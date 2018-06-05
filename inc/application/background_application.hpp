/**
 * File: background_application.hpp
 *
 * Description: Run a program as a unix daemon.
 * You need to override the run() method.
 */

#pragma once

#ifndef BACKGROUND_APPLICATION_HPP_
#define BACKGROUND_APPLICATION_HPP_

#include <signal.h>
#include <string>

class background_application
{
public:
    background_application() = default;
    virtual ~background_application() {};

    background_application(const background_application& copy) = delete;
    background_application& operator=(const background_application& copy) = delete;

    background_application(background_application&& copy) = delete;
    background_application& operator=(background_application&& copy) = delete;

    /**
     * @brief runs a program as a Unix daemon
     */
    void start_background() noexcept;

    /**
     * @brief main function
     */
    virtual void run() = 0;

private:
    /**
     * @brief create pid file contain pid number
     * current process
     *
     * @return bool status flag
     */
	bool create_pidfile(pid_t pid, std::string filename) const noexcept;

    /**
     * @brief remove pid file contain pid number
     * current process
     *
     * @return bool status flag
     */
    bool remove_pidfile(std::string filename) const noexcept;

    /**
     * @brief registration POSIX signals
     */
    void set_signals(sigset_t& sigset, siginfo_t& siginfo) const noexcept;

private:
    //! which process is running
    enum class process : pid_t { CHILD_PROCESS = 0, ERROR_PROCESS = -1 };
};

#endif //BACKGROUND_APPLICATION_HPP_
