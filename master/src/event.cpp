#include "event.hpp"

void StartJobEvent::send_update(
    const std::unique_ptr<PersistorService::Stub>& eucalypt_stub) {
  StartJobUpdateRequest request;
  PersistorReply reply;
  grpc::ClientContext context;

  request.set_job_uuid(job.get_job_uuid());
  request.set_job_user(job.get_job_user());
  request.set_binary_path(job.get_binary_path());
  request.set_mapper_name(job.get_mapper_name());
  request.set_reducer_name(job.get_reducer_name());
  request.set_m(job.get_M());
  request.set_r(job.get_R());
  request.set_ms(job_start_ms);

  auto status = eucalypt_stub->StartJobUpdate(&context, request, &reply);

  if (!status.ok()) {
    std::cout
        << "Warning, persistor failed to send start job update to Eucalypt: "
        << status.error_message() << std::endl;
  }
}

void StartTaskEvent::send_update(
    const std::unique_ptr<PersistorService::Stub>& eucalypt_stub) {
  StartTaskUpdateRequest request;
  PersistorReply reply;
  grpc::ClientContext context;

  auto task_input_file = task.get_task_input_file();

  request.set_task_uuid(task.get_task_uuid());
  request.set_job_uuid(task.get_job_uuid());
  request.set_task_type(task_input_file.has_value() ? "Map" : "Reduce");
  request.set_input_file(
      task_input_file.has_value() ? task_input_file.value().string() : "...");
  request.set_worker_socket(worker_socket_);
  request.set_idx(task.get_idx());
  request.set_ms(task_start_ms);

  auto status = eucalypt_stub->StartTaskUpdate(&context, request, &reply);

  if (!status.ok()) {
    std::cout
        << "Warning, persistor failed to send start task update to Eucalypt: "
        << status.error_message() << std::endl;
  }
}

void CompleteEvent::send_update(
    const std::unique_ptr<PersistorService::Stub>& eucalypt_stub) {
  CompleteEventUpdateRequest request;
  PersistorReply reply;
  grpc::ClientContext context;

  request.set_complete_event_type(event_type);
  request.set_uuid(event_uuid);
  request.set_ms(complete_ms);

  auto status = eucalypt_stub->CompleteEventUpdate(&context, request, &reply);

  if (!status.ok()) {
    std::cout << "Warning, persistor failed to send complete event update to "
                 "Eucalypt: "
              << status.error_message() << std::endl;
  }
}
