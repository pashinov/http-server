/**
 *  File: configuration_manager.hpp
 *
 *  Description: Configuration manager
 */

#pragma once

#ifndef CONFIGURATION_MANAGER_HPP_
#define CONFIGURATION_MANAGER_HPP_

#include <yaml-cpp/yaml.h>

#include <configuration_struct.hpp>
#include <singleton.hpp>

//////////////////////////////////////////////////////////////////////////
class configuration_manager : public singleton<configuration_manager>
{
public:
    configuration_manager();
    ~configuration_manager();

    configuration_manager(const configuration_manager& copy) = delete;
    configuration_manager& operator=(const configuration_manager& copy) = delete;

    configuration_manager(configuration_manager&& copy) = delete;
    configuration_manager& operator=(configuration_manager&& copy) = delete;

    /**
     * @brief load configuration file
     * @throw YAML::Exception
     */
    void load_config_file(std::string filename);

    /**
     * @brief reset configuration structure
     */
    void reset_config_struct();

    /**
     * @brief get configuration structure
     */
    const configuration_struct* get_config() noexcept;

private:
    /**
     * @brief get server name
     * @throw YAML::Exception
     */
    void get_server_name();

    /**
     * @brief gerp ap address
     * @throw YAML::Exception
     */
    void get_ip_address();

    /**
     * @brief get connection port
     * @throw YAML::Exception
     */
    void get_port();

    /**
     * @brief get document port
     * @throw YAML::Exception
     */
    void get_doc_root();

    /**
     * @brief get path to pid file
     * @throw YAML::Exception
     */
    void get_pidfile();

    /**
     * @brief get path to log file
     * @throw YAML::Exception
     */
    void get_logfile();


private:
    //! pointer to configuration structure
    static configuration_struct* cfg_;
    //! node that encapsulates YAML information
    YAML::Node config_ = YAML::Node(YAML::NodeType::Map);
};

#endif //CONFIGURATION_MANAGER_H_
