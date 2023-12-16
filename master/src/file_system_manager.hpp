#pragma once
#include <grpcpp/grpcpp.h>
#include <boost/filesystem.hpp>
#include <memory>
#include "master_service.pb.h"
#include "user.hpp"

namespace nfs {
namespace fs = boost::filesystem;

std::vector<fs::path> on_job_register_request(const std::string& uuid,
                                              const std::unique_ptr<User>& user,
                                              const std::string& file_regex);

// This should be called only if the job directory structure was successfully ensured
fs::path get_job_root_dir(const std::string& uuid,
                          const std::string& email);
}  // namespace nfs
