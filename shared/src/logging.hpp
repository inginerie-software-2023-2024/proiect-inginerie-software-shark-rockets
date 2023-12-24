#pragma once

#include <boost/log/trivial.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <string>
#include <mutex>

namespace logging {

// Forward declarations
namespace expr = boost::log::expressions;
namespace attrs = boost::log::attributes;

class Logger {
public:
    static Logger& get_instance();
    static void set_file_name(const std::string& file_name);
    static boost::log::sources::severity_logger_mt<boost::log::trivial::severity_level>& get_logger();

private:
    boost::log::sources::severity_logger_mt<boost::log::trivial::severity_level> logger_;
    std::string file_name_;
    bool initialized_ = false;

    Logger();
    void init_logging();
};

// Convenience macros
#define LOG_INFO(msg)    BOOST_LOG_SEV(logging::Logger::get_logger(), boost::log::trivial::info) << msg
#define LOG_WARNING(msg) BOOST_LOG_SEV(logging::Logger::get_logger(), boost::log::trivial::warning) << msg
#define LOG_ERROR(msg)   BOOST_LOG_SEV(logging::Logger::get_logger(), boost::log::trivial::error) << msg

} // namespace logging
