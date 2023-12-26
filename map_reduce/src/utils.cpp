#include "utils.hpp"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <iostream>
#include "logging.hpp"
#include "map_reduce.hpp"

std::string generate_uuid() {
  boost::uuids::uuid uuid = boost::uuids::random_generator()();
  return boost::uuids::to_string(uuid);
}

namespace po = boost::program_options;

std::istream& operator>>(std::istream& in, Mode& mode) {
  std::string token;
  in >> token;
  if (token == "user")
    mode = Mode::User;
  else if (token == "mapper")
    mode = Mode::Mapper;
  else if (token == "reducer")
    mode = Mode::Reducer;
  else
    in.setstate(std::ios_base::failbit);
  return in;
}

std::ostream& operator<<(std::ostream& out, const Mode& mode) {
  switch (mode) {
    case Mode::User:
      out << "Binary running in user mode, sending register to master"
          << std::endl;
      break;
    case Mode::Mapper:
      out << "Binary running in mapper mode, map will be executed" << std::endl;
      ;
      break;
    case Mode::Reducer:
      out << "Binary running in reducer mode, reduce will be executed"
          << std::endl;
      break;
  }
  return out;
}

std::unique_ptr<po::variables_map> parse_args(int argc, char** argv) {
  po::options_description desc("Options");
  desc.add_options()("help,h", "Print help messages")(
      "mode,o", po::value<Mode>(), "Operation mode: user, mapper, reducer")(
      "master-address,m",
      po::value<std::string>()->default_value("0.0.0.0:50051"),
      "Specify where the worker can find master: ip.ip.ip.ip:port")(
      "eucalypt-address,e",
      po::value<std::string>()->default_value("localhost:5555"),
      "Specify where Eucalypt backend can can be found: ip.ip.ip.ip:port")(
      "token,t", po::value<std::string>()->default_value(""),
      "Specify your connection token yo Eucalypt")(
      "class,c", po::value<std::string>(),
      "name of class to run, if mode is mapper or reducer")(
      "file,f", po::value<std::string>(), "input file for map task")(
      "job-root-dir,d", po::value<std::string>(),
      "absolute path to the root directory of the job")(
      "idx,x", po::value<int>(), "index of the task to run")(
      "m", po::value<int>(), "number of input files")("r", po::value<int>(),
                                                      "number of ouput files");
  desc.add(logging::Logger::get_logger_desc());

  try {
    auto vm = std::make_unique<po::variables_map>();
    po::store(po::parse_command_line(argc, argv, desc), *vm);
    po::notify(*vm);

    if (vm->count("help")) {
      std::cerr << "Koala CLI Interface: " << std::endl << desc << std::endl;
      exit(0);
    }
    if (!vm->count("mode")) {
      throw po::error("Mode not specified");
    }

    auto mode = get_arg<Mode>(vm, "mode");

    switch (mode) {
      case Mode::Mapper: {
        if (!vm->count("class")) {
          throw po::error("Mapper class not specified");
        }
        auto clss = get_arg<std::string>(vm, "class");
        if (!map_reduce::get_mappers().count(clss)) {
          throw po::error(clss + " not loaded in context");
        }
        break;
      }
      case Mode::Reducer: {
        if (!vm->count("class")) {
          throw po::error("Reducer class not specified");
        }
        auto clss = get_arg<std::string>(vm, "class");
        if (!map_reduce::get_reducers().count(clss)) {
          throw po::error(clss + " not loaded in context");
        }
        break;
      }
      case Mode::User:
        if (vm->count("class")) {
          throw po::error("User doesn't need class");
        }
        break;
      default:
        break;
    }

    return vm;
  } catch (const std::exception& e) {
    std::cerr << "Bad usage: " << e.what() << std::endl << desc << std::endl;
    exit(1);
  } catch (...) {
    std::cerr << "Unknow failure at parsing" << std::endl;
    exit(1);
  }
}
