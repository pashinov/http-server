#include <gtest/gtest.h>

#include <configuration_manager.hpp>

TEST(ConfManager, CorrectFile) {
    std::string filename = "config/server.yaml";
    configuration_manager::instance_ptr()->load_config_file(filename);

    std::string server_name = configuration_manager::instance_ptr()->get_config()->server_name_;
    ASSERT_EQ(server_name, "server");

    std::string ip_address = configuration_manager::instance_ptr()->get_config()->connection_ep_.ip_address_;
    ASSERT_EQ(ip_address, "127.0.0.1");

    std::uint16_t port = configuration_manager::instance_ptr()->get_config()->connection_ep_.port_;
    ASSERT_EQ(port, 12345);

    std::string logfile = configuration_manager::instance_ptr()->get_config()->paths_.log_.logfile_;
    ASSERT_EQ(logfile, "/var/log/server/logfile");

    std::string pidfile = configuration_manager::instance_ptr()->get_config()->paths_.pid_.pidfile_;
    ASSERT_EQ(pidfile, "/var/run/server.pid");
}

TEST(ConfManager, WrongFile) {

    std::string server_name;
    std::string ip_address;
    std::uint16_t port;
    std::string logfile;
    std::string pidfile;

    try
    {
        std::string filename = "tests/server_incorrect.yaml";
        configuration_manager::instance_ptr()->load_config_file(filename);
        server_name = configuration_manager::instance_ptr()->get_config()->server_name_;
        ip_address = configuration_manager::instance_ptr()->get_config()->connection_ep_.ip_address_;
        port = configuration_manager::instance_ptr()->get_config()->connection_ep_.port_;
        logfile = configuration_manager::instance_ptr()->get_config()->paths_.log_.logfile_;
        pidfile = configuration_manager::instance_ptr()->get_config()->paths_.pid_.pidfile_;
    }
    catch (...)
    {
        ASSERT_EQ(server_name, "");
        ASSERT_EQ(ip_address, "");
        ASSERT_EQ(port, 0);
        ASSERT_EQ(logfile, "");
        ASSERT_EQ(pidfile, "");
    }
}
