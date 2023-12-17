#pragma once

#include <grpcpp/grpcpp.h>
#include <atomic>
#include <memory>
#include <thread>
#include "health_service.grpc.pb.h"
#include "health_service.pb.h"

// Macros for constants
#define MAX_RETRIES 5
#define BASE_DELAY 2  // Base delay in seconds

template <typename F>
class Finally {
 public:
  explicit Finally(F f) : func(f) {}
  ~Finally() { func(); }

 private:
  F func;
};

template <typename F>
Finally<F> finally(F f) {
  return Finally<F>(f);
}
using failure_cb = std::function<void()>;
class HealthCheckMonitor {
 public:
  using Socket = std::pair<std::string, int>;
  HealthCheckMonitor(const std::shared_ptr<grpc::Channel>& channel,
                     const Socket& target, failure_cb cb_dead);
  ~HealthCheckMonitor();

 private:
  void MonitorHealth();
  std::shared_ptr<grpc::Channel> channel_;
  Socket target_;
  failure_cb cb_dead_;
  std::atomic<bool> running_;
  std::unique_ptr<std::thread> monitor_thread_;
};
