#include <boost/program_options.hpp>
#include <iostream>
#include <memory>

#include <application/application.hpp>
#include <conf_manager/configuration_manager.hpp>
#include <logger/logger.hpp>
#include <logger/logger_exception.hpp>
#include <common/utility.hpp>


namespace po = boost::program_options;


int main(int argc, char* argv[])
{
    po::options_description opts("service options");

    opts.add_options()
            ("help", "produce a help message")
            ("console", "run on console")
            ("daemon", "run as a service");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, opts), vm);

    if (vm.count("help") || argc == 1)
    {
        std::cout << opts << std::endl;
        return 0;
    }

    try
    {
        utility::initialization_config("/etc/http-server/http-server.yaml");
        utility::initialization_logger(configuration_manager::instance_ptr()->get_config()->paths_.log_.logfile_);
    }
    catch(logger_exception &ex)
    {
        std::cout << ex.what() << std::endl;
        exit(EXIT_FAILURE);
    }
    catch(YAML::Exception &ex)
    {
        std::cout << "configuration manager: " << ex.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    std::unique_ptr<application> app = std::make_unique<application>();

    if (vm.count("console"))
    {
        app->run();
    }
    else if (vm.count("daemon"))
    {
        app->start_background();
    }

    return 0;
}
