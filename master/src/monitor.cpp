#include "monitor.hpp"
#include "logging.hpp"
#include <chrono>
#include <cmath>

constexpr int calculateBucketDelay(int baseDelay, int retry) {
  return baseDelay * (1 << retry);  // Exponential backoff calculation
}

HealthCheckMonitor::HealthCheckMonitor(
    const std::shared_ptr<grpc::Channel>& channel, const Socket& target,
    failure_cb cb_dead)
    : channel_(channel), target_(target), cb_dead_(cb_dead), running_(true) {
  monitor_thread_ =
      std::make_unique<std::thread>(&HealthCheckMonitor::MonitorHealth, this);
}

HealthCheckMonitor::~HealthCheckMonitor() {
  running_ = false;
  if (monitor_thread_ && monitor_thread_->joinable()) {
    monitor_thread_->join();
  }
}

void HealthCheckMonitor::MonitorHealth() {
  // On monitor health scope end delete worker
  auto remove_worker = finally([&worker_socket = target_, &cb = cb_dead_]() {
    LOG_INFO << "Marking worker as innactive: " << worker_socket.first << ":"
              << worker_socket.second << std::endl;
    cb();
  });

  int retry_count = 0;
  while (running_) {
    auto stub_ = Health::NewStub(channel_);

    HealthCheckRequest request;
    request.set_service("worker");
    HealthCheckResponse response;
    grpc::ClientContext context;

    std::unique_ptr<grpc::ClientReader<HealthCheckResponse>> reader(
        stub_->Watch(&context, request));

    bool call_successful = false;
    while (running_ && reader->Read(&response)) {
      call_successful = true;
    }

    grpc::Status status = reader->Finish();
    if (!status.ok()) {
      // Handle deadline exceeded and other errors, ignore first error to avoid spam until connection is stable
      if (retry_count &&
          status.error_code() == grpc::StatusCode::DEADLINE_EXCEEDED) {
        LOG_WARNING << "Health check deadline exceeded" << std::endl;
      } else {
        LOG_WARNING << "Health check stream failed: " << status.error_message()
                  << std::endl;
      }
    }

    if (!call_successful) {
      if (retry_count >= MAX_RETRIES) {
        LOG_WARNING << "Maximum number of retries reached for target: "
                  << target_.first << ":" << target_.second
                  << " assume worker is dead" << std::endl;
        return;
      }

      int delay = calculateBucketDelay(BASE_DELAY, retry_count);
      std::this_thread::sleep_for(std::chrono::seconds(delay));
      retry_count++;
    } else {
      retry_count = 0;
      // Reset retry count if successful or max retries reached
    }
  }
}
