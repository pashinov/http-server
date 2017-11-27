/**
 *  File: logger.hpp
 *
 *  Description:
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <mutex>

#include <singleton.hpp>

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

    /**
     * @brief
     */
    void init_log_file(std::string filename);

    /**
     * @brief
     */
    void init_log_file(level log_level, std::string filename);

    /**
     * @brief
     */
    void set_log_level(level log_level) noexcept;

    /**
     * @brief
     */
    level get_log_level(void) const noexcept {return level_filter_;};

    /**
     * @brief
     */
    void log(level level, std::string message) const;

    /**
     * @brief
     */
    void clear_log_file() const;

private:
    /**
     * @brief
     */
    bool push(level level, std::string message) const noexcept;

    /**
     * @brief
     */
    std::string print(level level, std::string message) const noexcept;

private:
    //!
    level level_filter_;
    //!
    std::string filename_;
    //!
    mutable std::mutex mutex_log_;
};

#endif // LOGGER_H
