#pragma once
#include <grpcpp/grpcpp.h>
#include "health_service.grpc.pb.h"
#include "health_service.pb.h"

class HealthServiceImpl final : public Health::Service {
  grpc::Status Watch(grpc::ServerContext* context,
                     const HealthCheckRequest* request,
                     grpc::ServerWriter<HealthCheckResponse>* writer) override;
};
