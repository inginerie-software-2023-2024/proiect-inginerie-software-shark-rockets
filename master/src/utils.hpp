#pragma once
#include "shared_util.hpp"

namespace po = boost::program_options;
std::unique_ptr<po::variables_map> parse_args(int argc, char** argv);
