#include "worker.hpp"

Worker::Worker(std::string addr, int port)
    : addr_(std::move(addr)), port_(port), num_jobs(0) {
  std::string target = addr_ + ":" + std::to_string(port_);
  channel = grpc::CreateChannel(target, grpc::InsecureChannelCredentials());
  stub = WorkerService::NewStub(channel);
}

bool Worker::assign_work(const std::string& binary_path, WorkerType type,
                         const std::string& exec_class,
                         const std::string& input_file) {

  std::string mode = (type == WorkerType::Mapper) ? "mapper" : "reducer";

  grpc::ClientContext context;
  AssignWorkRequest request;
  request.set_path(binary_path);
  request.set_mode(mode);
  request.set_class_(exec_class);
  request.set_file(input_file);

  AssignWorkReply reply;
  auto status = stub->AssignWork(&context, request, &reply);

  if (!status.ok()) {
    throw std::runtime_error("Grpc call failed" + status.error_message());
  }

  if (reply.ok()) {
    num_jobs++;
  }

  return reply.ok();
}

const std::string& Worker::address() const {
  return addr_;
}

int Worker::port() const {
  return port_;
}

int Worker::load() const {
  return num_jobs;
}