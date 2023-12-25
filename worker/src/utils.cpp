#include "utils.hpp"
#include <iostream>
#include "logging.hpp"

std::unique_ptr<po::variables_map> parse_args(int argc, char** argv) {
  po::options_description desc("Options");
  desc.add_options()("help,h", "Print help messages")(
      "master-address,m",
      po::value<std::string>()->default_value("0.0.0.0:50051"),
      "Specify where the worker can find master: ip.ip.ip.ip:port")(
      "port,p", po::value<int>()->default_value(7777),
      "Set the port on which the worker will listen");
  desc.add(logging::Logger::get_logger_desc());

  try {
    auto vm = std::make_unique<po::variables_map>();
    po::store(po::parse_command_line(argc, argv, desc), *vm);
    po::notify(*vm);

    if (vm->count("help")) {
      std::cerr << "Worker CLI Interface: " << std::endl << desc << std::endl;
      exit(0);
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
