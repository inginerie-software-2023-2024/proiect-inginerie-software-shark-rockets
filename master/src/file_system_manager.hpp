#pragma once
#include <grpcpp/grpcpp.h>
#include <boost/filesystem.hpp>
#include <memory>
#include "master_service.pb.h"
#include "user.hpp"

namespace nfs {
namespace fs = boost::filesystem;

std::vector<fs::path> on_job_register_request(
    const std::string& uuid, const RegisterJobRequest* request);
}  // namespace nfs
