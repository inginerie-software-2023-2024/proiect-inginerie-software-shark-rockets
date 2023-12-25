#pragma once
#include <boost/program_options.hpp>
#include <string>
#include "shared_util.hpp"

std::string generate_uuid();

enum class Mode { User, Mapper, Reducer };

namespace po = boost::program_options;

std::unique_ptr<po::variables_map> parse_args(int argc, char** argv);
std::ostream& operator<<(std::ostream& out, const Mode& mode);
