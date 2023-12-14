#pragma once
#include <atomic>
#include <memory>
#include <thread>
#include "event.hpp"

class Persistor {
 private:
  // singleton
  static std::unique_ptr<Persistor> instance;

  // pending updates
  std::vector<std::unique_ptr<Event>> events;

  // sync primitives
  std::mutex persistor_lock;
  std::atomic_bool run_persistor_thread;
  std::thread persistor_thread;

  // channel to eucalypt
  std::shared_ptr<grpc::Channel> chan_to_eucalypt;
  std::unique_ptr<PersistorService::Stub> eucalypt_stub;

  Persistor(const std::string& eucalypt_grpc_address);

 public:
  static void set_eucalypt_address(const std::string& eucalypt_grpc_address);

  static std::unique_ptr<Persistor>& get_instance();

  void start_job(const StartJobEvent& event);

  void start_task(const StartTaskEvent& event);

  void complete_event(const CompleteEvent& event);

  void send_events();

  ~Persistor();
};
