#include "logging.hpp"
#include <boost/log/support/date_time.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <iostream>
#include <stdexcept>

namespace logging {

Logger& Logger::get_instance() {
  static Logger instance;
  return instance;
}

bool Logger::show_thread_id_ = false;  // Default to NOT showing thread ID

void Logger::show_thread_id(bool show) {
  show_thread_id_ = show;
}

severity_level Logger::log_level_ =
    severity_level::info;  // Default log level is INFO

void Logger::set_log_level(severity_level level) {
  log_level_ = level;
}

severity_level Logger::get_log_level() {
  return log_level_;
}

void Logger::set_file_name(const std::string& file_name) {
  Logger& instance = get_instance();
  instance.file_name_ =
      "./logs/" + file_name;  // XXX: future, dump logs in nfs with some logic
  instance.initialized_ = false;
}

boost::log::sources::severity_logger_mt<severity_level>& Logger::get_logger() {
  Logger& instance = get_instance();
  if (instance.file_name_.empty()) {
    throw std::runtime_error("Log file name not set.");
  }

  static std::once_flag flag;
  std::call_once(flag, [&instance]() { instance.init_logging(); });
  return instance.logger_;
}

Logger::Logger() = default;

void Logger::init_logging() {
  if (!initialized_) {
    namespace logging = boost::log;
    namespace keywords = boost::log::keywords;

    logging::add_common_attributes();

    auto formatter_lambda = [](boost::log::record_view const& rec,
                               boost::log::formatting_ostream& strm) {
      auto severity =
          rec.attribute_values()["Severity"].extract<severity_level>();
      std::string severity_str;
      if (severity) {
        switch (severity.get()) {
          case severity_level::trace:
            severity_str = "\033[34mTRACE\033[0m";
            break;
          case severity_level::info:
            severity_str = "\033[32mINFO\033[0m";
            break;
          case severity_level::warning:
            severity_str = "\033[33mWARNING\033[0m";
            break;
          case severity_level::error:
            severity_str = "\033[31mERROR\033[0m";
            break;
          case severity_level::fatal:
            severity_str = "\033[35mFATAL\033[0m";
            break;
          default:
            severity_str = "\033[0mUNKNOWN";
        }
      }

      auto timestamp =
          boost::log::extract<boost::posix_time::ptime>("TimeStamp", rec);

      strm << "[" << timestamp << "] ";
      if (show_thread_id_) {
        auto thread_id = boost::log::extract<
            boost::log::attributes::current_thread_id::value_type>("ThreadID",
                                                                   rec);
        strm << "[" << thread_id << "] ";
      }
      strm << "[" << severity_str << "] ";
      strm << rec[boost::log::expressions::smessage];
    };

    logging::add_console_log(std::cout, keywords::format = formatter_lambda);

    auto file_sink = logging::add_file_log(keywords::file_name = file_name_,
                                           keywords::format = formatter_lambda,
                                           keywords::auto_flush = true);

    initialized_ = true;
  }
}

}  // namespace logging
