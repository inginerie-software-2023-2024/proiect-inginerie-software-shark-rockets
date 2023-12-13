#pragma once
#include "job.hpp"
#include "persistor_service.grpc.pb.h"
#include "persistor_service.pb.h"
#include "task.hpp"
#include "worker.hpp"

// Events should know how to send their metadata to Eucalypt
// Therefore, specific events should inherit this base class and override send_update()
class Event {
 private:
  virtual void send_update(
      const std::unique_ptr<PersistorService::Stub>& eucalypt_stub) = 0;

 public:
  friend class Persistor;
};

class StartJobEvent : public Event {
 private:
  Job job;
  long long job_start_ms;

  void send_update(
      const std::unique_ptr<PersistorService::Stub>& eucalypt_stub) override;

 public:
  StartJobEvent(const Job& job, long long job_start_ms)
      : job(job), job_start_ms(job_start_ms){};
};

class StartTaskEvent : public Event {
 private:
  Task task;
  long long task_start_ms;
  std::string worker_socket_;

  void send_update(
      const std::unique_ptr<PersistorService::Stub>& eucalypt_stub) override;

 public:
  StartTaskEvent(const Task& task, long long task_start_ms,
                 const Socket& worker_socket)
      : task(task), task_start_ms(task_start_ms) {
    worker_socket_ =
        worker_socket.first + ":" + std::to_string(worker_socket.second);
  };
};

enum CompleteEventType { JobComplete = 0, TaskComplete = 1 };

class CompleteEvent : public Event {
 private:
  int event_type;
  std::string event_uuid;
  long long complete_ms;

  void send_update(
      const std::unique_ptr<PersistorService::Stub>& eucalypt_stub) override;

 public:
  CompleteEvent(CompleteEventType type, std::string uuid, long long complete_ms)
      : event_type(type), event_uuid(uuid), complete_ms(complete_ms){};
};
