#include "utils.hpp"
namespace nfs {
    
    bool ensure_directory(const fs::path &path) {
        if(fs::exists(path)) {
            return fs::is_directory(path);
        } else {
            return fs::create_directory(path);
        }
    }

    void sanity_check() {
        if(!fs::exists(NFS_ROOT)) {
            throw std::runtime_error("NFS not found");
        }
        if(!fs::is_directory(NFS_ROOT)) {
            throw std::runtime_error("NFS is not directory");
        }
    }
}
