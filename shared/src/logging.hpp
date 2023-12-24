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
  static void show_thread_id(bool show);
  static void set_log_level(severity_level level);
  static severity_level get_log_level();

 private:
  boost::log::sources::severity_logger_mt<severity_level> logger_;
  std::string file_name_;
  static severity_level log_level_;
  bool initialized_ = false;
  static bool show_thread_id_;

  Logger();
  void init_logging();
};

#ifdef NDEBUG  // Adds a way to build libkoala without logs

// Dummy macros

#define LOG_TRACE \
  if (false)      \
  BOOST_LOG_SEV(logging::Logger::get_logger(), logging::severity_level::trace)
#define LOG_INFO \
  if (false)     \
  BOOST_LOG_SEV(logging::Logger::get_logger(), logging::severity_level::info)
#define LOG_WARNING \
  if (false)        \
  BOOST_LOG_SEV(logging::Logger::get_logger(), logging::severity_level::warning)
#define LOG_ERROR \
  if (false)      \
  BOOST_LOG_SEV(logging::Logger::get_logger(), logging::severity_level::error)
#define LOG_FATAL \
  if (false)      \
  BOOST_LOG_SEV(logging::Logger::get_logger(), logging::severity_level::fatal)

#else

// Convenience macros

#define LOG_TRACE                                                         \
  if (logging::Logger::get_log_level() <= logging::severity_level::trace) \
  BOOST_LOG_SEV(logging::Logger::get_logger(), logging::severity_level::trace)
#define LOG_INFO                                                         \
  if (logging::Logger::get_log_level() <= logging::severity_level::info) \
  BOOST_LOG_SEV(logging::Logger::get_logger(), logging::severity_level::info)
#define LOG_WARNING                                                         \
  if (logging::Logger::get_log_level() <= logging::severity_level::warning) \
  BOOST_LOG_SEV(logging::Logger::get_logger(), logging::severity_level::warning)
#define LOG_ERROR                                                         \
  if (logging::Logger::get_log_level() <= logging::severity_level::error) \
  BOOST_LOG_SEV(logging::Logger::get_logger(), logging::severity_level::error)
#define LOG_FATAL                                                         \
  if (logging::Logger::get_log_level() <= logging::severity_level::fatal) \
  BOOST_LOG_SEV(logging::Logger::get_logger(), logging::severity_level::fatal)

#endif

}  // namespace logging
