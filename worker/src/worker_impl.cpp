#include "worker_impl.h"

WorkerServiceImpl::WorkerServiceImpl(std::string master_address)
    : WorkerService::Service(), master_address_(std::move(master_address)) {

  chan_to_master =
      grpc::CreateChannel(master_address_, grpc::InsecureChannelCredentials());
  master_stub = MasterService::NewStub(chan_to_master);
}

bool WorkerServiceImpl::notify_master(int port) {
  std::cout << "Worker: sending a register worker request with port " << port
            << '\n';

  RegisterWorkerRequest request;
  request.set_worker_port(port);

  RegisterWorkerReply reply;
  grpc::ClientContext context;
  auto status = master_stub->RegisterWorker(&context, request, &reply);

  if (!status.ok()) {
    throw std::runtime_error("Grpc call failed" + status.error_message());
  }

  return reply.ok();
}

grpc::Status WorkerServiceImpl::AssignWork(
    [[maybe_unused]] grpc::ServerContext* context,
    const AssignWorkRequest* request, AssignWorkReply* response) {

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
