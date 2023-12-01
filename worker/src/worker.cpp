#include <grpcpp/grpcpp.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include "master_service.grpc.pb.h"
#include "master_service.pb.h"
#include "worker_service.grpc.pb.h"
#include "worker_service.pb.h"

// Should parse arguments with boost...
std::string parse_address(int argc, char** argv) {
  if (argc < 3)
    throw std::runtime_error("Invalid usage, expected 2 arguments");

  return argv[1];
}

int parse_port(int argc, char** argv) {
  if (argc < 3)
    throw std::runtime_error("Invalid usage, expected 2 arguments");

  return std::stoi(argv[2]);
}

// Should have some worker state, which should persist the channel to the master service
void notify_master(const std::string& master_address, int port) {
  auto channel =
      grpc::CreateChannel(master_address, grpc::InsecureChannelCredentials());
  auto master_service = MasterService::NewStub(channel);

  std::cout << "Worker: sending a register worker request with port " << port
            << '\n';

  RegisterWorkerRequest request;
  request.set_worker_port(port);

  RegisterWorkerReply reply;
  grpc::ClientContext context;
  auto status = master_service->RegisterWorker(&context, request, &reply);

  if (status.ok())
    std::cout << "Worker: success, got " << reply.ok() << " from master\n";
  else
    std::cout << "Worker: failure, status is not ok\n";
}

class WorkerServiceImpl final : public WorkerService::Service {
 public:
  grpc::Status AssignWork([[maybe_unused]] grpc::ServerContext* context,
                          const AssignWorkRequest* request,
                          AssignWorkReply* response) override {
    std::cout << "Worker: received an assign work request:"
              << " path: " << request->path() << ','
              << " mode: " << request->mode() << ','
              << " class: " << request->class_() << ','
              << " file : " << request->file() << '\n';

    // Fork a new process and run the job!
    pid_t child_pid = fork();
    if (child_pid == -1) {
      response->set_ok(false);
      return grpc::Status::OK;
    } else if (child_pid > 0) {
      response->set_ok(true);
      return grpc::Status::OK;
    } else {
      char *path = strdup("does_not_matter"),
           *master_ip = strdup("does_not_matter"),
           *mode = strdup(request->mode().c_str()),
           *class_ = strdup(request->class_().c_str());
      char* arguments[] = {path, master_ip, mode, class_, NULL};
      execve(request->path().c_str(), arguments, NULL);
    }
    return grpc::Status::CANCELLED;
  }
};

int main(int argc, char** argv) {
  // Parse master's address
  std::string master_address = parse_address(argc, argv);

  // Parse worker's gRPC port
  int port = parse_port(argc, argv);

  // Signal to master that we're up
  notify_master(master_address, port);

  // Start a grpc server, waiting for work to be assigned
  WorkerServiceImpl worker_service;
  grpc::ServerBuilder builder;

  builder.AddListeningPort("0.0.0.0:" + std::to_string(port),
                           grpc::InsecureServerCredentials());
  builder.RegisterService(&worker_service);

  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

  std::cout << "Worker: listening on port " << port << '\n';
  server->Wait();

  return 0;
}
