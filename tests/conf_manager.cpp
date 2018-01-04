#include <gtest/gtest.h>

#include <configuration_manager.hpp>

TEST(ConfManager, ConfManagerTest) {
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
