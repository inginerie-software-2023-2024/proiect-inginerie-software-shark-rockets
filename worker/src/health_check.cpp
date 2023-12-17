#include <chrono>
#include <thread>
#include "heatlh_check.hpp"

grpc::Status HealthServiceImpl::Watch(
    [[maybe_unused]] grpc::ServerContext* context,
    [[maybe_unused]] const HealthCheckRequest* request,
    grpc::ServerWriter<HealthCheckResponse>* writer) {
  while (true) {
    HealthCheckResponse response;
    response.set_status(HealthCheckResponse::SERVING);
    writer->Write(response);
    std::this_thread::sleep_for(std::chrono::seconds(2));
  }
  return grpc::Status::OK;
}
