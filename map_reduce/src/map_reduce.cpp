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
      std::cout << "Map task with index " << idx << " has input file "
                << get_arg<std::string>(vm, "file") << '\n';

      get_mappers()[clss]->map();

      exit(0);
      break;
    }
    case Mode::Reducer: {
      auto clss = get_arg<std::string>(vm, "class");
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
