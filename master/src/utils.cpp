#include "utils.hpp"
namespace nfs {
    
    bool ensure_directory(const fs::path &path) {
        if(fs::exists(path)) {
            return fs::is_directory(path);
        } else {
            return fs::create_directory(path);
        }
    }
}
