#pragma once
#include <boost/program_options.hpp>
#include <string>

std::string generate_uuid();

enum class Mode { User, Mapper, Reducer };

namespace po = boost::program_options;

std::unique_ptr<po::variables_map> parse_args(int argc, char** argv);
std::ostream& operator<<(std::ostream& out, const Mode& mode);

template <typename T>
T get_arg(const std::unique_ptr<po::variables_map>& vm,
          const std::string& key) {
  if (!vm->count(key)) {
    throw std::logic_error("Accesing a argument that was not parsed");
  }
  return (*vm)[key].as<T>();
}
