#include "worker.hpp"

Worker::Worker(std::string addr, int listen_port, int emit_port)
    : addr_(std::move(addr)), listen_port_(listen_port), emit_port_(emit_port) {
  std::string target = addr_ + ":" + std::to_string(listen_port_);
  channel = grpc::CreateChannel(target, grpc::InsecureChannelCredentials());
  stub = WorkerService::NewStub(channel);
}

bool Worker::assign_work(const std::string& binary_path, JobLeg job_leg,
                         const std::string& exec_class,
                         const std::string& input_file,
                         const std::string& task_uuid) {

  std::string mode = (job_leg == JobLeg::Map) ? "mapper" : "reducer";

  grpc::ClientContext context;
  AssignWorkRequest request;
  request.set_path(binary_path);
  request.set_mode(mode);
  request.set_class_(exec_class);
  request.set_file(input_file);
  request.set_task_uuid(task_uuid);

  AssignWorkReply reply;
  auto status = stub->AssignWork(&context, request, &reply);

  if (!status.ok()) {
    throw std::runtime_error("Grpc call failed" + status.error_message());
  }

  if (reply.ok()) {
    assigned_tasks.insert(task_uuid);
  }

  return reply.ok();
}

const std::string& Worker::address() const {
  return addr_;
}

Socket Worker::get_emit_socket() const {
  return {addr_, emit_port_};
}

int Worker::listen_port() const {
  return listen_port_;
}

int Worker::load() const {
  return assigned_tasks.size();
}

void Worker::finish_task(const std::string& task_uuid) {
  assigned_tasks.erase(task_uuid);
}
