/**
 * File: daemon.h
 *
 * Description: Run a program as a Unix daemon.
 * You need to override the run() method.
 */

#include <signal.h>

#ifndef DAEMON_H_
#define DAEMON_H_

class daemon
{
public:
    daemon() = default;
    ~daemon() = default;

    /**
     * @brief daemonize runs a program as a Unix daemon
     * @throw TODO
     */
    void daemonize() const;

    daemon(const daemon& copy) = delete;
    daemon& operator=(const daemon& copy) = delete;

private:
    /**
     * @brief user function (must be overridden)
     * @throw TODO
     */
	void run() const;

    /**
     * @brief write pid number to file
     * @return bool status flag
     */
	bool write_pid(pid_t pid, std::string filename) const noexcept;

    /**
     * @brief add POSIX signal sets
     */
    void set_signal(sigset_t& sigset, siginfo_t& siginfo) const noexcept;

private:
    //! which process runs
    enum class type_process : pid_t { CHILD_PROCESS = 0, ERROR_PROCESS = -1 };
};

#endif // DAEMON_H_
