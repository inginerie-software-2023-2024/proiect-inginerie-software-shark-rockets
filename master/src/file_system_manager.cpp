#include "file_system_manager.hpp"
#include "utils.hpp"
#include <boost/regex.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <iostream>
#include <vector>

namespace nfs {

    std::vector<fs::path> list_files_matching_pattern(
        const fs::path& base_path,
        const std::string& regex_pattern
    ) {
        std::vector<fs::path> matching_files;

        boost::regex pattern = boost::regex(regex_pattern);

        fs::recursive_directory_iterator end_iter; // Default construction yields past-the-end
        for (fs::recursive_directory_iterator iter(base_path); iter != end_iter; ++iter) {
            if (fs::is_regular_file(iter->status())) {
                fs::path relative_path = fs::relative(iter->path(), base_path);

                if (boost::regex_match(relative_path.string(), pattern)) {
                    matching_files.push_back(iter->path());
                }
            }
        }

        return matching_files;
    }

    bool create_job_structure(const fs::path &job_root) {
        if(!ensure_directory(job_root)) {
            std::cerr << "Failed to ensure job root " << job_root << std::endl;
            return false;
        }

        for(const auto& job_dir : {"input","intermediary","output"}) {
            if(!ensure_directory(job_root / job_dir)) {
                std::cerr << "Failed to ensure job dir" << job_root << std::endl;
                return false;
            }
        }
        return true;
    }


    std::vector<fs::path> sym_link_data(const std::vector<fs::path> &files,const fs::path &job_root) {
        
        fs::path input_dir = job_root / "input";

        std::vector<fs::path> linked_files;
        linked_files.reserve(files.size());

        for (size_t i = 0; i < files.size(); ++i) {
            fs::path input_link = input_dir / ("f-" + std::to_string(i));
            fs::path rel_path = fs::relative(files[i],input_dir);

            fs::create_symlink(rel_path,input_link);

            linked_files.push_back(input_link);
        }

        return linked_files;
    }


    std::vector<fs::path> on_job_register_request(const grpc::ServerContext *context,const RegisterJobRequest *request) {

        std::unique_ptr<User> user;
        if(request->has_user_name()) {
            user = std::make_unique<User>(request->user_name());
        } else {
            user = std::make_unique<User>(); // Guest
        }

        fs::path user_dir = NFS_ROOT / user->get_name();
        fs::path user_data_dir = user_dir / "data";
        
        if(!nfs::ensure_directory(user_data_dir)) {
            std::cerr << "Failed to ensure directory: " << user_data_dir << std::endl;
            return {};
        }

        std::vector<fs::path> files = list_files_matching_pattern(user_data_dir,request->file_regex());
        
        const auto &metadata = context->client_metadata();
        auto uuid_it = metadata.find("uuid");
        std::string uuid;

        if (uuid_it != metadata.end()) {
            uuid = std::string(uuid_it->second.data(), uuid_it->second.size());
            std::cout << "Request UUID: " << uuid << std::endl;
        } else {
            std::cerr << "Request doesnt have uuid " << std::endl;
            return {};
        }

        fs::path job_root = user_dir / ("job-" + uuid);

        if(!create_job_structure(job_root)) {
            std::cerr << "Creating job structure failed " << std::endl;
            return {};
        }

        try {
            return sym_link_data(files,job_root);
        } catch (const fs::filesystem_error& e) {
            std::cerr << "Creating symbolic links failed, defaulting to normal paths, error=" << e.what() << std::endl;
            return files;
        }
    }
}
