#include "worker_impl.hpp"

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

void WorkerServiceImpl::wait_then_notify_master(pid_t pid) {
  int pstatus;
  int pid_ret = waitpid(pid, &pstatus, 0);
  if (pid_ret == -1) {
    std::cerr << "Waitpid failed!" << std::endl;
  }

  AckWorkerFinishRequest request;
  AckWorkerFinishReply reply;
  grpc::ClientContext context;

  auto status = master_stub->AckWorkerFinish(&context, request, &reply);

  if (!status.ok()) {
    std::cerr << "Grpc call failed:" << status.error_message() << std::endl;
  }
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
    // Capture "this" and child_pid.
    // Note: "this" will always be a valid pointer, because
    // we join() the threads in the destructor: the threads cannot outlive "this".
    auto f = [this, child_pid] {
      this->wait_then_notify_master(child_pid);
    };

    // Create a new thread that will wait until the process stops and
    // then notify the master. Add it to the list of notify_threads.
    notify_threads.push_back(std::thread(f));

    response->set_ok(true);
    return grpc::Status::OK;
  } else {
    char *path = strdup("does_not_matter"),
         *mode = strdup(request->mode().c_str()),
         *class_ = strdup(request->class_().c_str());
    char* arguments[] = {
        path, strdup("--mode"), mode, strdup("--class"), class_, NULL};
    execve(request->path().c_str(), arguments, NULL);
  }
  return grpc::Status::CANCELLED;
}

WorkerServiceImpl::~WorkerServiceImpl() {
  for (std::thread& t : notify_threads) {
    t.join();
  }
}
