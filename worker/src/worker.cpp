#include <grpcpp/grpcpp.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include "health_check.hpp"
#include "logging.hpp"
#include "utils.hpp"
#include "worker_impl.hpp"

int main(int argc, char** argv) {
  logging::Logger::set_file_name("worker.log");

  auto vm = parse_args(argc, argv);
  std::string master_address = get_arg<std::string>(vm, "master-address");
  int port = get_arg<int>(vm, "port");

  WorkerServiceImpl worker_service(master_address);
  bool ok = worker_service.notify_master(port);
  if (ok) {
    LOG_INFO << "Master was notified successfully" << std::endl;
  } else {
    LOG_ERROR << "Something went wrong when notifying the master." << std::endl;
  }
  HealthServiceImpl health_service;

  // Start a grpc server, waiting for work to be assigned
  grpc::ServerBuilder builder;

  builder.AddListeningPort("0.0.0.0:" + std::to_string(port),
                           grpc::InsecureServerCredentials());
  builder.RegisterService(&worker_service);
  builder.RegisterService(&health_service);

  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

  LOG_INFO << "Worker: listening on port " << port << '\n';
  server->Wait();

  return 0;
}
