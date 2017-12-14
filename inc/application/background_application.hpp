/**
 * File: background_application.hpp
 *
 * Description: Run a program as a unix daemon.
 * You need to override the run() method.
 */

#include <signal.h>
#include <string>

#ifndef BACKGROUND_APPLICATION_H_
#define BACKGROUND_APPLICATION_H_

class background_application
{
public:
    background_application() = default;
    virtual ~background_application() {};

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
     * @return bool status flag
     */
	bool create_pidfile(pid_t pid, std::string filename) const noexcept;

    /**
     * @brief remove pid file contain pid number
     * current process
     * @return bool status flag
     */
    bool remove_pidfile(std::string filename) const noexcept;

    /**
     * @brief add POSIX signal sets
     */
    void set_signal(sigset_t& sigset, siginfo_t& siginfo) const noexcept;

private:
    //! which process running
    enum class process : pid_t { CHILD_PROCESS = 0, ERROR_PROCESS = -1 };
};

#endif // BACKGROUND_APPLICATION_H_
