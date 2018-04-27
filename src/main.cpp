#include <iostream>
#include <memory>

#include <application.hpp>
#include <configuration_manager.hpp>
#include <logger.hpp>
#include <logger_exception.hpp>
#include <utility.hpp>

int main(int argc, char* argv[])
{
    try
    {
        utility::initialization_config("/etc/http-server/http-server.yaml");
        utility::initialization_logger(configuration_manager::instance_ptr()->get_config()->paths_.log_.logfile_);
    }
    catch(logger_exception &ex)
    {
        std::cout << ex.what() << std::endl;
    }
    catch(YAML::Exception &ex)
    {
        std::cout << "configuration manager: " << ex.what() << std::endl;
    }

    std::unique_ptr<application> app = std::make_unique<application>();
    app->start_background();

    return 0;
}
