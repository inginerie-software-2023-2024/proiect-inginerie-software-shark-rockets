#include <grpcpp/grpcpp.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include "health_check.hpp"
#include "utils.hpp"
#include "worker_impl.hpp"

int main(int argc, char** argv) {

  auto vm = parse_args(argc, argv);
  std::string master_address = get_arg<std::string>(vm, "master-address");
  int port = get_arg<int>(vm, "port");

  WorkerServiceImpl worker_service(master_address);
  bool ok = worker_service.notify_master(port);
  if (ok) {
    std::cout << "Master was notified successfully" << std::endl;
  } else {
    std::cout << "Something went wrong when notifying the master." << std::endl;
  }
  HealthServiceImpl health_service;

  // Start a grpc server, waiting for work to be assigned
  grpc::ServerBuilder builder;

  builder.AddListeningPort("0.0.0.0:" + std::to_string(port),
                           grpc::InsecureServerCredentials());
  builder.RegisterService(&worker_service);
  builder.RegisterService(&health_service);

  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

  std::cout << "Worker: listening on port " << port << '\n';
  server->Wait();

  return 0;
}
