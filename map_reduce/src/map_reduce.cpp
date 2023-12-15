#include "map_reduce.hpp"
#include <grpcpp/grpcpp.h>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include "master_service.grpc.pb.h"
#include "master_service.pb.h"
#include "utils.hpp"

namespace map_reduce {

// Backend of mapper class
struct Mapper::impl {
  std::vector<std::pair<std::string, std::string>>* drain_;

  void set_drain(std::vector<std::pair<std::string, std::string>>* drain) {
    drain_ = drain;
  }

  void emit(const std::string& key, const std::string& value) {
    drain_->emplace_back(key, value);
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

void ensure_intermediary_files(const std::string& job_root_dir, int idx,
                               int R) {
  fs::path intermediary_dir = fs::path(job_root_dir) / "intermediary";

  for (int i = 0; i < R; i++) {
    // opening and closing a file - a.k.a touch
    std::string file_name = std::to_string(idx) + "-" + std::to_string(i);
    auto f = fs::ofstream(intermediary_dir / file_name);
    f.close();
  }
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
  std::cout << mode;

  switch (mode) {
    case Mode::Mapper: {
      const auto clss = get_arg<std::string>(vm, "class");
      auto idx = get_arg<int>(vm, "idx");

      // Log mapper input file
      std::string input_file = get_arg<std::string>(vm, "file");
      std::cout << "Map task with index " << idx << " has input file "
                << input_file << '\n';

      // Create r intermediary files
      ensure_intermediary_files(get_arg<std::string>(vm, "job-root-dir"), idx,
                                get_arg<int>(vm, "r"));

      // set drain
      std::vector<std::pair<std::string, std::string>> kvs;
      get_mappers()[clss]->pImpl->set_drain(&kvs);

      // pass the user-provided map function each line in the input file
      fs::ifstream in(input_file);
      std::string line;

      while (getline(in, line)) {
        get_mappers()[clss]->map(line);

        // process emitted pairs
        for (const auto& p : kvs) {
          std::cout << "User emitted " << p.first << ' ' << p.second << '\n';
          kvs.clear();
        }
      }

      in.close();

      exit(0);
      break;
    }
    case Mode::Reducer: {
      auto clss = get_arg<std::string>(vm, "class");
      auto idx = get_arg<int>(vm, "idx"), m = get_arg<int>(vm, "m");

      // Find reducer input files
      std::vector<fs::path> input_files = get_reducer_input_files(
          get_arg<std::string>(vm, "job-root-dir"), idx);

      if ((int)input_files.size() != m) {
        std::cout << "Warning: expected " << m
                  << " intermediary files for index " << idx << ", found "
                  << input_files.size() << '\n';

      } else {
        std::cout << "Found all intermediary files for index " << idx << '\n';
      }

      get_reducers()[clss]->reduce();

      exit(0);
      break;
    }
    case Mode::User: {
      const auto master_adress = get_arg<std::string>(vm, "master-address");
      const auto channel = grpc::CreateChannel(
          master_adress, grpc::InsecureChannelCredentials());
      master_service = MasterService::NewStub(channel);
      break;
    }
    default:
      break;
  }
}

void map_reduce::register_job(const std::string& mapper_name,
                              const std::string& reducer_name,
                              const std::string& file_regex, int R,
                              const std::string& user_name) {
  // check that the provided mapper and reducer are known ...

  std::cout << "User: sending a register job request with mapper "
            << mapper_name << " and reducer " << reducer_name << '\n';

  RegisterJobRequest request;
  request.set_path(get_executable_path());
  request.set_mapper(mapper_name);
  request.set_reducer(reducer_name);
  request.set_file_regex(file_regex);
  request.set_r(R);

  if (user_name != "")
    request.set_user_name(user_name);  // send optional parameter

  RegisterJobReply reply;
  grpc::ClientContext context;
  context.AddMetadata("uuid", generate_uuid());

  auto status = master_service->RegisterJob(&context, request, &reply);

  if (status.ok())
    std::cout << "User: success, got " << reply.ok() << " from master\n";
  else
    std::cout << "User: failure, status is not ok\n";
}
