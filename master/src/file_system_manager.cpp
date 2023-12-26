#include "file_system_manager.hpp"
#include <boost/algorithm/string/replace.hpp>
#include <boost/regex.hpp>
#include <iostream>
#include <vector>
#include "logging.hpp"
#include "utils.hpp"

namespace nfs {

std::vector<fs::path> list_files_matching_pattern(
    const fs::path& base_path, const std::string& regex_pattern) {
  std::vector<fs::path> matching_files;

  if (!fs::exists(base_path)) {
    return matching_files;
  }

  boost::regex pattern = boost::regex(regex_pattern);

  fs::recursive_directory_iterator
      end_iter;  // Default construction yields past-the-end
  for (fs::recursive_directory_iterator iter(base_path); iter != end_iter;
       ++iter) {
    if (fs::is_regular_file(iter->status())) {
      fs::path relative_path = fs::relative(iter->path(), base_path);

      if (boost::regex_match(relative_path.string(), pattern)) {
        matching_files.push_back(iter->path());
      }
    }
  }

  return matching_files;
}

bool create_job_structure(const fs::path& job_root) {

  if (!ensure_directory(job_root)) {
    LOG_ERROR << "Failed to ensure job root " << job_root << std::endl;
    return false;
  }

  for (const auto& job_dir : {"input", "intermediary", "output"}) {
    if (!ensure_directory(job_root / job_dir)) {
      LOG_ERROR << "Failed to ensure job dir" << job_root << std::endl;
      return false;
    }
  }
  return true;
}

std::vector<fs::path> sym_link_data(const std::vector<fs::path>& files,
                                    const fs::path& job_root) {

  fs::path input_dir = job_root / "input";

  if (!fs::exists(input_dir)) {
    boost::system::error_code ec(boost::system::errc::no_such_file_or_directory,
                                 boost::system::generic_category());
    throw fs::filesystem_error("Input dir not found", job_root.c_str(), ec);
  }

  std::vector<fs::path> linked_files;
  linked_files.reserve(files.size());

  for (size_t i = 0; i < files.size(); ++i) {
    if (!fs::exists(files[i])) {
      boost::system::error_code ec(
          boost::system::errc::no_such_file_or_directory,
          boost::system::generic_category());
      throw fs::filesystem_error("Can't symlink to nonexistent file",
                                 files[i].c_str(), ec);
    }

    fs::path input_link = input_dir / ("f-" + std::to_string(i));
    fs::path rel_path = fs::relative(files[i], input_dir);

    fs::create_symlink(rel_path, input_link);

    linked_files.push_back(input_link);
  }

  return linked_files;
}

std::vector<fs::path> on_job_register_request(const std::string& uuid,
                                              const std::unique_ptr<User>& user,
                                              const std::string& file_regex) {

  fs::path user_dir = NFS_ROOT / user->get_email();
  fs::path user_data_dir = user_dir / "data";

  if (!nfs::ensure_directory(user_data_dir)) {
    LOG_ERROR << "Failed to ensure directory: " << user_data_dir << std::endl;
    return {};
  }

  std::vector<fs::path> files =
      list_files_matching_pattern(user_data_dir, file_regex);
  fs::path job_root = user_dir / ("job-" + uuid);

  if (!create_job_structure(job_root)) {
    LOG_ERROR << "Creating job structure failed " << std::endl;
    return {};
  }

  try {
    return sym_link_data(files, job_root);
  } catch (const fs::filesystem_error& e) {
    LOG_ERROR
        << "Creating symbolic links failed, defaulting to normal paths, error="
        << e.what() << std::endl;
    return files;
  }
}

fs::path get_job_root_dir(const std::string& uuid, const std::string& email) {
  fs::path job_root_dir = NFS_ROOT / email / ("job-" + uuid);
  return job_root_dir;
}
}  // namespace nfs
