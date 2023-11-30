#pragma once
#include <grpcpp/grpcpp.h>
#include <memory>
#include <boost/filesystem.hpp>
#include "user.hpp"
#include "master_service.pb.h"


namespace nfs {
    namespace fs = boost::filesystem;
    
    std::vector<fs::path> on_job_register_request(const grpc::ServerContext *context,const RegisterJobRequest *request);
}
