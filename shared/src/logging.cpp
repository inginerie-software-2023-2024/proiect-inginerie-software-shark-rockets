#include "logging.hpp"
#include <boost/log/support/date_time.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <iostream>
#include <stdexcept>
#include "shared_util.hpp"

namespace logging {

Logger& Logger::get_instance() {
  static Logger instance;
  return instance;
}

bool Logger::show_thread_id_;

void Logger::show_thread_id(bool show) {
  show_thread_id_ = show;
}

severity_level Logger::log_level_;

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

std::istream& operator>>(std::istream& in, severity_level& level) {
  std::string token;
  in >> token;
  if (token == "trace")
    level = severity_level::trace;
  else if (token == "info")
    level = severity_level::info;
  else if (token == "warning")
    level = severity_level::warning;
  else if (token == "error")
    level = severity_level::error;
  else if (token == "fatal")
    level = severity_level::fatal;
  else
    in.setstate(std::ios_base::failbit);
  return in;
}

std::ostream& operator<<(std::ostream& out, const severity_level& level) {
  switch (level) {
    case severity_level::trace:
      out << "Severity Level: TRACE";
      break;
    case severity_level::info:
      out << "Severity Level: INFO";
      break;
    case severity_level::warning:
      out << "Severity Level: WARNING";
      break;
    case severity_level::error:
      out << "Severity Level: ERROR";
      break;
    case severity_level::fatal:
      out << "Severity Level: FATAL";
      break;
  }
  return out;
}

po::options_description Logger::get_logger_desc() {
  po::options_description desc("Logging Options");
  desc.add_options()(
      "log-severity-level,l", po::value<severity_level>(),
      "Set the log severity level (trace, info, warning, error, fatal)")(
      "thread-id,t", po::bool_switch(), "Include thread ID in logs")(
      "file,f", po::value<std::string>(), "Set custom log file");
  return desc;
}

void Logger::load_cli_config([[maybe_unused]] const std::unique_ptr<
                                 boost::program_options::variables_map>& vm,
                             const std::string& default_file) {
  auto file = get_optional_arg<std::string>(vm, "file").value_or(default_file);
  Logger::set_file_name(file);

  auto thread_id = get_optional_arg<bool>(vm, "thread-id").value_or(false);
  Logger::show_thread_id(thread_id);

  auto log_level = get_optional_arg<severity_level>(vm, "log-severity-level")
                       .value_or(severity_level::info);
  Logger::set_log_level(log_level);
}

}  // namespace logging
