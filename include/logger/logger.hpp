/**
 *  File: logger.hpp
 *
 *  Description: Logger class
 */

#pragma once

#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include <mutex>

#include <common/singleton.hpp>

//////////////////////////////////////////////////////////////////////////
enum class level // level is incremental, i.e. info contains warning
{
    debug   = 0,
    verbose = 1,
    info    = 2,
    normal  = 3, // default logging level
    warning = 4,
    error   = 5
};

//////////////////////////////////////////////////////////////////////////
class logger : public singleton<logger>
{
public:
    logger();
    ~logger() = default;

    logger(const logger& copy) = delete;
    logger& operator=(const logger& copy) = delete;

    logger(logger&& copy) = delete;
    logger& operator=(logger&& copy) = delete;

    /**
     * @brief initialization logfile
     * @throw logger_exception
     */
    void init_log_file(std::string filename);

    /**
     * @brief initialization logfile
     * @throw logger_exception
     */
    void init_log_file(level log_level, std::string filename);

    /**
     * @brief set default log level
     */
    void set_log_level(level log_level) noexcept;

    /**
     * @brief get current default log level
     */
    level get_log_level(void) const noexcept {return level_filter_;};

    /**
     * @brief write log message
     * @throw logger_exception
     */
    void log(std::string message) const;

    /**
     * @brief write log message
     * @throw logger_exception
     */
    void log(level level, std::string message) const;

    /**
     * @brief clear log file
     * @throw logger_exception
     */
    void clear_log_file() const;

private:
    /**
     * @brief write log message
     * @return status bool flag
     */
    bool push(level level, std::string message) const noexcept;

    /**
     * @brief create string which will write to log file (datetime + level + message)
     * @return created message
     */
    std::string print(level level, std::string message) const noexcept;

private:
    //! level filter for log messages
    level level_filter_;
    //! log filename
    std::string filename_;
    //! mutex
    mutable std::mutex mutex_log_;
};

#endif //LOGGER_HPP_
