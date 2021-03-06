#include <gtest/gtest.h>

#include <conf_manager/configuration_manager.hpp>

#include "userpaths.h"

TEST(ConfManager, CorrectFile)
{
    std::string filename = CONF_PATH;
    configuration_manager::instance_ptr()->load_config_file(filename);

    std::string server_name = configuration_manager::instance_ptr()->get_config()->server_name_;
    ASSERT_EQ(server_name, "http-server");

    std::string ip_address = configuration_manager::instance_ptr()->get_config()->connection_ep_.ip_address_;
    ASSERT_EQ(ip_address, "127.0.0.1");

    std::string port = configuration_manager::instance_ptr()->get_config()->connection_ep_.port_;
    ASSERT_EQ(port, "12345");

    std::string logfile = configuration_manager::instance_ptr()->get_config()->paths_.log_.logfile_;
    ASSERT_EQ(logfile, "/var/log/http-server/logfile");

    std::string pidfile = configuration_manager::instance_ptr()->get_config()->paths_.pid_.pidfile_;
    ASSERT_EQ(pidfile, "/var/run/http-server.pid");

    configuration_manager::instance_ptr()->reset_config_struct();
}

TEST(ConfManager, IncorrectName)
{
    std::string filename = "tests/configs/incorrect_name.yaml";
    EXPECT_THROW(configuration_manager::instance_ptr()->load_config_file(filename), YAML::Exception);

    std::string server_name = configuration_manager::instance_ptr()->get_config()->server_name_;
    ASSERT_EQ(server_name, "");

    configuration_manager::instance_ptr()->reset_config_struct();
}

TEST(ConfManager, IncorrectAddress)
{
    std::string filename = "tests/configs/incorrect_address.yaml";
    EXPECT_THROW(configuration_manager::instance_ptr()->load_config_file(filename), YAML::Exception);

    std::string ip_address = configuration_manager::instance_ptr()->get_config()->connection_ep_.ip_address_;
    ASSERT_EQ(ip_address, "");

    configuration_manager::instance_ptr()->reset_config_struct();
}

TEST(ConfManager, IncorrectPort)
{
    std::string filename = "tests/configs/incorrect_port.yaml";
    EXPECT_THROW(configuration_manager::instance_ptr()->load_config_file(filename), YAML::Exception);

    std::string port = configuration_manager::instance_ptr()->get_config()->connection_ep_.port_;
    ASSERT_EQ(port, "");

    configuration_manager::instance_ptr()->reset_config_struct();
}

TEST(ConfManager, IncorrectDocRoot)
{
    std::string filename = "tests/configs/incorrect_doc_root.yaml";
    EXPECT_THROW(configuration_manager::instance_ptr()->load_config_file(filename), YAML::Exception);

    std::string doc_root = configuration_manager::instance_ptr()->get_config()->connection_ep_.doc_root_;
    ASSERT_EQ(doc_root, "");

    configuration_manager::instance_ptr()->reset_config_struct();
}

TEST(ConfManager, IncorrectPidfile)
{
    std::string filename = "tests/configs/incorrect_pidfile.yaml";
    EXPECT_THROW(configuration_manager::instance_ptr()->load_config_file(filename), YAML::Exception);

    std::string pidfile = configuration_manager::instance_ptr()->get_config()->paths_.pid_.pidfile_;
    ASSERT_EQ(pidfile, "");

    configuration_manager::instance_ptr()->reset_config_struct();
}

TEST(ConfManager, IncorrectLogfile)
{
    std::string filename = "tests/configs/incorrect_logfile.yaml";
    EXPECT_THROW(configuration_manager::instance_ptr()->load_config_file(filename), YAML::Exception);

    std::string logfile = configuration_manager::instance_ptr()->get_config()->paths_.log_.logfile_;
    ASSERT_EQ(logfile, "");

    configuration_manager::instance_ptr()->reset_config_struct();
}
