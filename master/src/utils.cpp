#include "utils.hpp"

namespace nfs {

bool ensure_directory(const fs::path& path) {
  if (fs::exists(path)) {
    return fs::is_directory(path);
  } else {
    return fs::create_directory(path);
  }
}

void sanity_check() {
  if (!fs::exists(NFS_ROOT)) {
    throw std::runtime_error(std::string("NFS not found ") +
                             (NFS_ROOT).string());
  }
  if (!fs::is_directory(NFS_ROOT)) {
    throw std::runtime_error(std::string("NFS is not a directory ") +
                             (NFS_ROOT).string());
  }
}
}  // namespace nfs

namespace uuid {

std::string generate_uuid() {
  boost::uuids::uuid uuid = boost::uuids::random_generator()();
  return boost::uuids::to_string(uuid);
}
}  // namespace uuid
