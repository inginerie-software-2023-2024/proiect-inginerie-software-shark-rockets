#include "worker.hpp"
#include "logging.hpp"

Worker::Worker(std::string addr, int listen_port, int emit_port,
               reassign_cb failure_cb)
    : addr_(std::move(addr)), listen_port_(listen_port), emit_port_(emit_port) {
  std::string target = addr_ + ":" + std::to_string(listen_port_);
  channel = grpc::CreateChannel(target, grpc::InsecureChannelCredentials());
  stub = WorkerService::NewStub(channel);

  auto on_failure = [&active = active_, &tasks = assigned_tasks,
                     cb = std::move(failure_cb)]() {
    active = false;
    cb(tasks);
  };
  monitor_ = std::make_unique<HealthCheckMonitor>(channel, get_emit_socket(),
                                                  std::move(on_failure));
}

bool Worker::assign_work(const Job& job, const Task& task) {
  std::optional<nfs::fs::path> input_file = task.get_task_input_file();
  std::string input_file_str =
      input_file.has_value() ? input_file.value().string() : "does_not_matter";

  LOG_INFO << "Assign task " << task.get_task_uuid() << ", index "
           << task.get_idx() << " to " << address() << ":" << listen_port()
           << " with load = " << load() << ", input file: " << input_file_str
           << std::endl;

  std::string mode =
      (job.get_current_leg() == JobLeg::Map) ? "mapper" : "reducer";

  grpc::ClientContext context;
  AssignWorkRequest request;
  request.set_path(job.get_binary_path());
  request.set_job_root_dir(
      nfs::get_job_root_dir(job.get_job_uuid(), job.get_job_user()).string());
  request.set_mode(mode);
  request.set_class_(job.get_exec_class());
  request.set_file(input_file_str);
  request.set_task_uuid(task.get_task_uuid());
  request.set_idx(task.get_idx());
  request.set_m(job.get_M());
  request.set_r(job.get_R());

  auto deadline = std::chrono::system_clock::now() + std::chrono::seconds(1);  // 1 second from now
  context.set_deadline(deadline);

  AssignWorkReply reply;
  auto status = stub->AssignWork(&context, request, &reply);

  if (!status.ok()) {
    throw std::runtime_error("Grpc call failed" + status.error_message());
  }

  if (reply.ok()) {
    assigned_tasks.insert(task.get_task_uuid());
  }

  return reply.ok();
}

const std::string& Worker::address() const {
  return addr_;
}

Socket Worker::get_emit_socket() const {
  return {addr_, emit_port_};
}

Socket Worker::get_listen_socket() const {
  return {addr_, listen_port_};
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

bool Worker::is_active() const {
  return active_.load();
}
