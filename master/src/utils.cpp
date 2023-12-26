#include "utils.hpp"
#include <iostream>
#include "logging.hpp"

std::unique_ptr<po::variables_map> parse_args(int argc, char** argv) {
  po::options_description desc("Options");
  desc.add_options()("help,h", "Print help messages")(
      "eucalypt-address,e",
      po::value<std::string>()->default_value("localhost:5555"),
      "Specify where the master can find Eucalypt node-api: ip.ip.ip.ip:port");
  desc.add(logging::Logger::get_logger_desc());

  try {
    auto vm = std::make_unique<po::variables_map>();
    po::store(po::parse_command_line(argc, argv, desc), *vm);
    po::notify(*vm);

    if (vm->count("help")) {
      std::cerr << "Master CLI Interface: " << std::endl << desc << std::endl;
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
