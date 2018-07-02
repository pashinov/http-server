#include <memory>

#include <application/application.hpp>
#include <conf_manager/configuration_manager.hpp>
#include <logger/logger.hpp>
#include <http_server/server.hpp>

void application::run() noexcept
{
    std::string address;
    std::string port;
    std::string doc_root;

    try
    {
        address = configuration_manager::instance_ptr()->get_config()->connection_ep_.ip_address_;
        port = configuration_manager::instance_ptr()->get_config()->connection_ep_.port_;
        doc_root = configuration_manager::instance_ptr()->get_config()->connection_ep_.doc_root_;
    }
    catch (YAML::Exception &ex)
    {
        std::string msg = "configuration_manager: " + std::string(ex.what());
        logger::instance_ptr()->log(level::error, msg);
    }

    std::unique_ptr<http::server::server> http_server =
            std::make_unique<http::server::server>(address, port, doc_root);
    http_server->run();
}
