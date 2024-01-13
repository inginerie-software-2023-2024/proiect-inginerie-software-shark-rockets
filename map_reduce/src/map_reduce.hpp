#pragma once
#include <boost/filesystem.hpp>
#include <string>
#include "koala.hpp"
#include "master_service.grpc.pb.h"
#include "master_service.pb.h"

namespace map_reduce {
namespace fs = boost::filesystem;

std::unordered_map<std::string, Mapper*>& get_mappers();
std::unordered_map<std::string, Reducer*>& get_reducers();

void ensure_intermediary_files(const std::string& job_root_dir, int idx, int R);
std::vector<fs::path> get_reducer_input_files(const std::string& job_root_dir,
                                              int idx);

class KVManager {
 private:
  std::unordered_map<std::string, std::unique_ptr<fs::ifstream>>
      file_name_to_handle;
  std::unordered_map<std::string, std::pair<std::string, std::string>>
      file_name_to_kv;
  std::optional<std::string> min_key;
  std::string min_key_file_name;

  bool read_kv(const std::string& file_name);

 public:
  KVManager(const std::vector<fs::path>& reducer_input_files);

  bool has_next_key() const;
  std::optional<std::string> get_next_key();
  std::optional<std::string> get_value_for_key(const std::string& key);

  ~KVManager();
};
}  // namespace map_reduce
