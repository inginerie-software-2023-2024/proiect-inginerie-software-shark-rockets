#pragma once
#include <boost/filesystem.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <chrono>
#include <string>

namespace nfs {
namespace fs = boost::filesystem;

#ifdef DOCKER_BUILD
#define NFS_ROOT fs::path("/nfs")
#else
#define NFS_ROOT fs::path(std::getenv("HOME")) / "nfs"
#endif

bool ensure_directory(const fs::path& path);
void sanity_check();
}  // namespace nfs

namespace uuid {
std::string generate_uuid();
}  // namespace uuid

namespace time_utils {
using namespace std::chrono;
long long get_time();
}  // namespace time_utils
