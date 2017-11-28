#include <cassert>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#include <configuration_manager.hpp>
#include <daemon.hpp>

void daemon::daemonize() const
{
	pid_t pid = fork();

    switch (pid)
    {
        case static_cast<pid_t>(daemon::type_process::CHILD_PROCESS):
        {
            chdir("/");
            setsid();
            umask(0);

            close(STDIN_FILENO);
            close(STDOUT_FILENO);
            close(STDERR_FILENO);

            pid_t pid = fork();

            switch(pid)
            {
                case static_cast<pid_t>(daemon::type_process::CHILD_PROCESS):
                {
                    daemon::run();
                    break;
                }

                case static_cast<pid_t>(daemon::type_process::ERROR_PROCESS):
                {
                    throw; // TODO
                }

                default:
                {
                    daemon::write_pid(getpid(), configuration_manager::instance().get_config()->paths_.pid_.pidfile_);

                    sigset_t sigset;
                    siginfo_t siginfo;

                    daemon::set_signal(sigset, siginfo);

                    sigwaitinfo(&sigset, &siginfo);

                    if (siginfo.si_signo == SIGCHLD)
                    {
                        waitpid(pid, 0, WNOHANG);
                        exit(EXIT_SUCCESS);
                    }
                    else if (siginfo.si_signo == SIGUSR1)
                    {
                        kill(pid, SIGKILL); // TODO
                        exit(EXIT_SUCCESS);
                    }
                    break;
                }
            }

            break;
        }

        case static_cast<pid_t>(daemon::type_process::ERROR_PROCESS):
        {
            throw;
        }

        default:
        {
            exit(EXIT_SUCCESS);
        }
    }
}

void daemon::run() const
{
    // TODO
}

bool daemon::write_pid(pid_t pid, std::string filename) const noexcept
{
    assert(!filename.empty());

    std::ofstream stream;
    stream.open(filename, std::ios::out);
    if(!stream.is_open()) { return true; }
    std::string spid = std::to_string(pid);
    stream.write(spid.c_str(), spid.size());
    stream.close();

    return false;
}

void daemon::set_signal(sigset_t& sigset, siginfo_t& siginfo) const noexcept
{
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGUSR1);
    sigaddset(&sigset, SIGCHLD);
    sigprocmask(SIG_BLOCK, &sigset, nullptr);
}
