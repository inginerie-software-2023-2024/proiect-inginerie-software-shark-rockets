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
}  // namespace map_reduce
