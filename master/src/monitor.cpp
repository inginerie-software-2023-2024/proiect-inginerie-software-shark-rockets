#include "monitor.hpp"
#include <chrono>
#include <cmath>

constexpr int calculateBucketDelay(int baseDelay, int retry) {
  return baseDelay * (1 << retry);  // Exponential backoff calculation
}

HealthCheckMonitor::HealthCheckMonitor(
    const std::shared_ptr<grpc::Channel>& channel, const Socket& target)
    : channel_(channel), target_(target), running_(true) {
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
  auto remove_worker = finally([&worker_socket = target_]() {
    std::cout << "Eliminating worker: " << worker_socket.first << ":"
              << worker_socket.second << std::endl;
    // TO DO: implement cleanup logic
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
      // Handle deadline exceeded and other errors
      if (status.error_code() == grpc::StatusCode::DEADLINE_EXCEEDED) {
        std::cerr << "Health check deadline exceeded" << std::endl;
      } else {
        std::cerr << "Health check stream failed: " << status.error_message()
                  << std::endl;
      }
    }

    if (!call_successful) {
      if (retry_count >= MAX_RETRIES) {
        std::cerr << "Maximum number of retries reached for target: "
                  << target_.first << ":" << target_.second
                  << " assume worker is dead" << std::endl;
        return;
      }

      int delay = calculateBucketDelay(BASE_DELAY, retry_count);
      std::this_thread::sleep_for(std::chrono::seconds(delay));
      retry_count++;
    } else {
      retry_count =
          0;  // Reset retry count if successful or max retries reached
    }
  }
}
