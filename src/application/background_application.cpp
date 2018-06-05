#include <cassert>
#include <fstream>
#include <sys/prctl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#include <background_application.hpp>
#include <configuration_manager.hpp>
#include <logger.hpp>

void background_application::start_background() noexcept
{
    pid_t pid;
    pid = fork();

    switch (pid)
    {
        case static_cast<pid_t>(background_application::process::CHILD_PROCESS):
        {
            pid_t sid;

            /* Change the file mode mask */
            umask(0);

            /* Create a new SID for the child process */
            sid = setsid();
            if (sid < 0)
            {
                logger::instance_ptr()->log(level::error, "Failed to create new SID for child process");
                std::exit(EXIT_FAILURE);
            }

            /* Change the current working directory */
            if ((chdir("/")) < 0)
            {
                logger::instance_ptr()->log(level::error, "Failed to set working directory");
                std::exit(EXIT_FAILURE);
            }

            /* Close out the standard file descriptors */
            close(STDIN_FILENO);
            close(STDOUT_FILENO);
            close(STDERR_FILENO);

            pid_t pid;
            pid = fork();

            switch(pid)
            {
                case static_cast<pid_t>(background_application::process::CHILD_PROCESS):
                {
                    logger::instance_ptr()->log(level::info, "Starting HTTP server.");

                    this->run();
                    break;
                }

                case static_cast<pid_t>(background_application::process::ERROR_PROCESS):
                {
                    logger::instance_ptr()->log(level::error, "Failed to create worker process");
                    std::exit(EXIT_FAILURE);
                }

                default:
                {
                    if (background_application::create_pidfile(getpid(), configuration_manager::instance().get_config()->
                            paths_.pid_.pidfile_))
                    {
                        logger::instance_ptr()->log(level::error, "Failed to create pidfile");
                        std::exit(EXIT_FAILURE);
                    }

                    sigset_t sigset;
                    siginfo_t siginfo;

                    background_application::set_signals(sigset, siginfo);

                    sigwaitinfo(&sigset, &siginfo);

                    if (siginfo.si_signo == SIGCHLD)
                    {
                        if (background_application::remove_pidfile(configuration_manager::instance().get_config()->
                                paths_.pid_.pidfile_))
                        {
                            waitpid(pid, 0, WNOHANG);
                            std::exit(EXIT_SUCCESS);
                        }
                        else
                        {
                            logger::instance_ptr()->log(level::error, "Failed to remove pidfile");
                            std::exit(EXIT_FAILURE);
                        }
                    }
                    else if (siginfo.si_signo == SIGUSR1)
                    {
                        if (background_application::remove_pidfile(configuration_manager::instance().get_config()->
                                paths_.pid_.pidfile_))
                        {
                            kill(pid, SIGUSR1);
                            logger::instance_ptr()->log(level::info, "HTTP server was stopped.");
                            std::exit(EXIT_SUCCESS);
                        }
                        else
                        {
                            logger::instance_ptr()->log(level::error, "Failed to remove pidfile");
                            std::exit(EXIT_FAILURE);
                        }
                    }
                    break;
                }
            }

            break;
        }

        case static_cast<pid_t>(background_application::process::ERROR_PROCESS):
        {
            logger::instance_ptr()->log(level::error, "Failed to create master process");
            std::exit(EXIT_FAILURE);
        }

        default:
        {
            std::exit(EXIT_SUCCESS);
        }
    }
}

bool background_application::create_pidfile(pid_t pid, std::string filename) const noexcept
{
    assert(!filename.empty());

    std::ofstream stream;
    stream.open(filename, std::ios::out);
    if(!stream.is_open()) { return true; };
    std::string spid = std::to_string(pid);
    stream.write(spid.c_str(), spid.size());
    stream.close();

    return false;
}

bool background_application::remove_pidfile(std::string filename) const noexcept
{
    assert(!filename.empty());

    if (std::remove(filename.c_str())) { return true; };

    return false;
}

void background_application::set_signals(sigset_t& sigset, siginfo_t& siginfo) const noexcept
{
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGUSR1);
    sigaddset(&sigset, SIGCHLD);
    sigprocmask(SIG_BLOCK, &sigset, nullptr);
}
