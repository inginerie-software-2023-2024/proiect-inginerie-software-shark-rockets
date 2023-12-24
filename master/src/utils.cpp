#include "utils.hpp"
#include <iostream>

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

namespace time_utils {

long long get_time() {
  milliseconds ms =
      duration_cast<milliseconds>(system_clock::now().time_since_epoch());
  return ms.count();
}
}  // namespace time_utils

std::unique_ptr<po::variables_map> parse_args(int argc, char** argv) {
  po::options_description desc("Options");
  desc.add_options()("help,h", "Print help messages")(
      "eucalypt-address,e",
      po::value<std::string>()->default_value("localhost:5555"),
      "Specify where the master can find Eucalypt node-api: ip.ip.ip.ip:port");

  try {
    auto vm = std::make_unique<po::variables_map>();
    po::store(po::parse_command_line(argc, argv, desc), *vm);
    po::notify(*vm);

    if (vm->count("help")) {
      std::cerr << "Master CLI Interface: " << std::endl << desc << std::endl;
      exit(0);
    }

    return vm;
  } catch (const std::exception& e) {
    std::cerr << "Bad usage: " << e.what() << std::endl << desc << std::endl;
    exit(1);
  } catch (...) {
    std::cerr << "Unknow failure at parsing" << std::endl;
    exit(1);
  }
}
