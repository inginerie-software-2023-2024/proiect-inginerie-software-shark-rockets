#include "map_reduce.hpp"
#include <grpcpp/grpcpp.h>
#include <iostream>
#include <memory>
#include <set>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include "logging.hpp"
#include "master_service.grpc.pb.h"
#include "master_service.pb.h"
#include "utils.hpp"

namespace map_reduce {

using KVs = std::set<std::pair<std::string, std::string>>;

// Backend of mapper class
struct Mapper::impl {
  KVs* drain_;

  void set_drain(KVs* drain) { drain_ = drain; }

  void emit(const std::string& key, const std::string& value) {
    drain_->insert(std::make_pair(key, value));
  }
};

Mapper::Mapper() : pImpl{std::make_unique<impl>()} {}

void Mapper::emit(const std::string& key, const std::string& value) {
  pImpl->emit(key, value);
}

Mapper::~Mapper() = default;

// Avoid static initialization order fiasco with construct on first use idiom (and constinit)
// I feel this can be improved :)

constinit std::unique_ptr<MasterService::Stub> master_service;
std::string CLI_token;

std::string& get_executable_path() {
  static std::string executable_path;
  return executable_path;
}

std::unordered_map<std::string, Mapper*>& get_mappers() {
  static std::unordered_map<std::string, Mapper*> mappers;
  return mappers;
}

std::unordered_map<std::string, Reducer*>& get_reducers() {
  static std::unordered_map<std::string, Reducer*> reducers;
  return reducers;
}

std::vector<fs::path> get_reducer_input_files(const std::string& job_root_dir,
                                              int idx) {
  fs::path intermediary_dir = fs::path(job_root_dir) / "intermediary";
  std::vector<fs::path> reducer_input_files;

  fs::recursive_directory_iterator
      end_iter;  // Default construction yields past-the-end
  for (fs::recursive_directory_iterator iter(intermediary_dir);
       iter != end_iter; ++iter) {
    fs::path intermediary_file = iter->path();
    std::string intermediary_file_name = intermediary_file.filename().string();

    std::size_t dash = intermediary_file_name.find('-');
    if (dash == std::string::npos)
      continue;
    int file_idx = std::stoi(intermediary_file_name.substr(
        dash + 1, (int)intermediary_file_name.size() - dash));

    if (idx == file_idx)
      reducer_input_files.push_back(intermediary_file);
  }

  return reducer_input_files;
}

}  // namespace map_reduce

bool map_reduce::register_mapper(const std::string& name, Mapper* mapper) {
  // check mappers are not registered after map_reduce::init() is called
  get_mappers()[name] = mapper;
  return true;
}

bool map_reduce::register_reducer(const std::string& name, Reducer* reducer) {
  // check reducers are not registered after map_reduce::init() is called
  get_reducers()[name] = reducer;
  return true;
}

void map_reduce::init(int argc, char** argv) {
  auto vm = parse_args(argc, argv);
  get_executable_path() = argv[0];

  auto mode = get_arg<Mode>(vm, "mode");

  switch (mode) {
    case Mode::Mapper: {
      const auto clss = get_arg<std::string>(vm, "class");
      auto idx = get_arg<int>(vm, "idx");
      logging::Logger::load_cli_config(vm, "koala/koala-mapper-" + clss + "-" +
                                               std::to_string(idx) + ".log");
      LOG_INFO << mode;

      // Log mapper input file
      std::string input_file = get_arg<std::string>(vm, "file");
      LOG_INFO << "Map task with index " << idx << " has input file "
               << input_file << '\n';

      // Create r intermediary temporary files
      const std::string job_root_dir = get_arg<std::string>(vm, "job-root-dir"),
                        rand_uuid = generate_uuid();
      int r = get_arg<int>(vm, "r");
      fs::path intermediary_dir = fs::path(job_root_dir) / "intermediary";

      std::vector<fs::path> intermediary_output_paths;  // for renaming, later
      std::vector<std::unique_ptr<fs::ofstream>>
          intermediary_output_streams;  // for writing intermediary kvs
      for (int i = 0; i < r; i++) {
        std::string temorary_file_name = rand_uuid + "-" + std::to_string(i);
        fs::path temporary_file_path = intermediary_dir / temorary_file_name;

        intermediary_output_paths.emplace_back(temporary_file_path);
        intermediary_output_streams.emplace_back(
            std::make_unique<fs::ofstream>(temporary_file_path.string()));
      }

      // set drain
      KVs kvs;
      get_mappers()[clss]->pImpl->set_drain(&kvs);

      // pass the user-provided map function each line in the input file
      fs::ifstream in(input_file);
      std::string line;

      // this is a naive implementation, as it keeps all emitted key-value pairs in memory
      // should flush to disk periodically as memory fills up, then merge the sorted files
      while (getline(in, line)) {
        get_mappers()[clss]->map(line);
      }

      in.close();

      // process emitted pairs
      for (const auto& p : kvs) {
        // write the emitted kv to the appropriate file
        std::size_t intermediary_file_idx =
            std::hash<std::string>{}(p.first) % r;
        *intermediary_output_streams[intermediary_file_idx] << p.first << ' '
                                                            << p.second << '\n';
      }

      // rename temporary intermediary files
      for (int i = 0; i < r; i++) {
        intermediary_output_streams[i]->close();

        std::string permanent_file_name =
            std::to_string(idx) + "-" + std::to_string(i);
        fs::rename(intermediary_output_paths[i],
                   intermediary_dir / permanent_file_name);
      }

      exit(0);
      break;
    }
    case Mode::Reducer: {
      auto clss = get_arg<std::string>(vm, "class");
      auto idx = get_arg<int>(vm, "idx"), m = get_arg<int>(vm, "m");
      logging::Logger::load_cli_config(vm, "koala/koala-reducer-" + clss + "-" +
                                               std::to_string(idx) + ".log");
      LOG_INFO << mode;

      // Find reducer input files
      std::vector<fs::path> input_files = get_reducer_input_files(
          get_arg<std::string>(vm, "job-root-dir"), idx);

      if ((int)input_files.size() != m) {
        LOG_WARNING << "Expected " << m << " intermediary files for index "
                    << idx << ", found " << input_files.size() << '\n';

      } else {
        LOG_INFO << "Found all intermediary files for index " << idx << '\n';
      }

      get_reducers()[clss]->reduce();

      exit(0);
      break;
    }
    case Mode::User: {
      logging::Logger::load_cli_config(vm, "koala/koala-user.log");
      LOG_INFO << mode;

      CLI_token = get_arg<std::string>(vm, "token");
      const auto master_adress = get_arg<std::string>(vm, "master-address");
      const auto master_channel = grpc::CreateChannel(
          master_adress, grpc::InsecureChannelCredentials());
      master_service = MasterService::NewStub(master_channel);
      break;
    }
    default:
      break;
  }
}

map_reduce::job_uuid map_reduce::register_job(const std::string& mapper_name,
                                              const std::string& reducer_name,
                                              const std::string& file_regex,
                                              int R, const std::string& token) {
  // check that the provided mapper and reducer are known ...

  LOG_INFO << "User: sending a register job request with mapper " << mapper_name
           << " and reducer " << reducer_name << '\n';

  RegisterJobRequest request;
  request.set_path(get_executable_path());
  request.set_mapper(mapper_name);
  request.set_reducer(reducer_name);
  request.set_file_regex(file_regex);
  request.set_r(R);

  if (CLI_token == "")
    request.set_token(token);
  else
    request.set_token(CLI_token);

  RegisterJobReply reply;
  grpc::ClientContext contextMaster;
  std::string uuid = generate_uuid();

  contextMaster.AddMetadata("uuid", uuid);

  auto register_status =
      master_service->RegisterJob(&contextMaster, request, &reply);

  if (register_status.ok()) {
    LOG_INFO << "User: success, got " << reply.ok() << " from master\n";
  } else {
    if (register_status.error_code() == grpc::StatusCode::RESOURCE_EXHAUSTED) {
      LOG_INFO << "User: " << register_status.error_message() << '\n';
    } else {
      LOG_INFO << "Connection: failure, status is not ok\n";
    }
  }
  return uuid;
}

void map_reduce::join_job(const job_uuid& job) {
  JoinJobRequest request;
  JoinJobReply reply;
  grpc::ClientContext context;

  request.set_job_uuid(job);
  auto status = master_service->JoinJob(&context, request, &reply);

  if (status.ok()) {
    LOG_INFO << "User: join(" << job << ") sucess." << std::endl;
  } else {
    LOG_ERROR << "User: join(" << job << ") failed: " << status.error_message()
              << std::endl;
  }
}
