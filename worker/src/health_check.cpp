#include "health_check.hpp"
#include <chrono>
#include <thread>

grpc::Status HealthServiceImpl::Watch(
    [[maybe_unused]] grpc::ServerContext* context,
    [[maybe_unused]] const HealthCheckRequest* request,
    grpc::ServerWriter<HealthCheckResponse>* writer) {
  while (true) {
    HealthCheckResponse response;
    // This could be extended to show the health of the worker
    response.set_status(HealthCheckResponse::SERVING);
    writer->Write(response);
    std::this_thread::sleep_for(std::chrono::seconds(10));
  }
  return grpc::Status::OK;
}