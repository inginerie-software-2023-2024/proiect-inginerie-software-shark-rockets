#pragma once
#include <boost/filesystem.hpp>
#include <string>

namespace nfs {
    namespace fs = boost::filesystem;

    #ifdef DOCKER_BUILD
    #define NFS_ROOT fs::path("/nfs")
    #else
    #define NFS_ROOT fs::path(std::getenv("HOME")) / "nfs"
    #endif

    bool ensure_directory(const fs::path &path);
}


