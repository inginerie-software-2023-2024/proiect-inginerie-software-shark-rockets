#pragma once

#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/trivial.hpp>
#include <mutex>
#include <string>

namespace logging {

enum class severity_level { trace, info, warning, error, fatal };

// Logger is a singleton class that provides formatted logs to stdout and a user specified file as well as some macros for convenience
class Logger {
 public:
  static Logger& get_instance();
  static void set_file_name(const std::string& file_name);
  static boost::log::sources::severity_logger_mt<severity_level>& get_logger();

 private:
  boost::log::sources::severity_logger_mt<severity_level> logger_;
  std::string file_name_;
  bool initialized_ = false;

  Logger();
  void init_logging();
};

// Convenience macros

#define LOG_TRACE \
  BOOST_LOG_SEV(logging::Logger::get_logger(), logging::severity_level::trace)
#define LOG_INFO \
  BOOST_LOG_SEV(logging::Logger::get_logger(), logging::severity_level::info)
#define LOG_WARNING \
  BOOST_LOG_SEV(logging::Logger::get_logger(), logging::severity_level::warning)
#define LOG_ERROR \
  BOOST_LOG_SEV(logging::Logger::get_logger(), logging::severity_level::error)
#define LOG_FATAL \
  BOOST_LOG_SEV(logging::Logger::get_logger(), logging::severity_level::fatal)

}  // namespace logging
