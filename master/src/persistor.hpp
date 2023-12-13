#pragma once
#include <atomic>
#include <memory>
#include <thread>
#include "event.hpp"

class Persistor {
 private:
  // pending updates
  std::vector<std::unique_ptr<Event>> events;

  // sync primitives
  std::mutex persistor_lock;
  std::atomic_bool run_persistor_thread;
  std::thread persistor_thread;

  // channel to eucalypt
  std::shared_ptr<grpc::Channel> chan_to_eucalypt;
  std::unique_ptr<PersistorService::Stub> eucalypt_stub;

 public:
  Persistor(const std::string& eucalypt_grpc_address);

  void start_job(const StartJobEvent& event);

  void start_task(const StartTaskEvent& event);

  void complete_event(const CompleteEvent& event);

  void send_events();

  ~Persistor();
};
