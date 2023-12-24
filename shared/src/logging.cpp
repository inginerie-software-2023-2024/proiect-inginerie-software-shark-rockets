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

void Logger::set_file_name(const std::string& file_name) {
  Logger& instance = get_instance();
  instance.file_name_ = file_name;
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
      auto thread_id = boost::log::extract<
          boost::log::attributes::current_thread_id::value_type>("ThreadID",
                                                                 rec);
      auto timestamp =
          boost::log::extract<boost::posix_time::ptime>("TimeStamp", rec);

      strm << "[" << timestamp << "] "
           << "[" << thread_id << "] "
           << "[" << severity_str << "] "
           << rec[boost::log::expressions::smessage];
    };

    logging::add_console_log(std::cout, keywords::format = formatter_lambda);

    auto file_sink = logging::add_file_log(keywords::file_name = file_name_,
                                           keywords::format = formatter_lambda,
                                           keywords::auto_flush = true);

    initialized_ = true;
  }
}

}  // namespace logging
