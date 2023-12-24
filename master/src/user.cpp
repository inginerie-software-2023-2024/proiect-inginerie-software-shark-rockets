#include "user.hpp"
#include <iostream>
#include "logging.hpp"
#include "utils.hpp"

User::User(std::string email) : email(email) {

  // If an user is created master makes a directory for him, as well as a data subdirectory
  // all subsequent data will be only added to data
  bool u_nfs_ok = true;
  u_nfs_ok &= nfs::ensure_directory(nfs::NFS_ROOT / email);
  u_nfs_ok &= nfs::ensure_directory(nfs::NFS_ROOT / email / "data");

  if (!u_nfs_ok) {
    LOG_ERROR << "Failure, user doesn't have dirs" << std::endl;
  }
}

std::string User::get_email() const {
  return email;
}
