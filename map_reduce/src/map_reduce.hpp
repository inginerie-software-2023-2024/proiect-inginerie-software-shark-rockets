#pragma once
#include <string>
#include "koala.hpp"
#include "master_service.grpc.pb.h"
#include "master_service.pb.h"

namespace map_reduce {
std::unordered_map<std::string, Mapper*>& get_mappers();
std::unordered_map<std::string, Reducer*>& get_reducers();
}  // namespace map_reduce
