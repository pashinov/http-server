/**
 *  File: configuration_manager.hpp
 *
 *  Description: Configuration manager
 */

#ifndef CONFIGURATION_MANAGER_H_
#define CONFIGURATION_MANAGER_H_

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

    /**
     * @brief load configuration file
     * @throw YAML::ParserException
     */
	void load_config_file(std::string filename);

    /**
     * @brief get configuration structure
     */
	const configuration_struct* get_config() noexcept;

private:
	/**
	 * @brief get server name
	 * @throw YAML::ParserException
	 */
	void get_server_name();

	/**
	 * @brief gerp ap address
	 * @throw YAML::ParserException
	 */
	void get_ip_address();

	/**
	 * @brief get connection port
	 * @throw YAML::ParserException
	 */
	void get_port();

    /**
     * @brief get path to pid file
     * @throw YAML::ParserException
     */
    void get_pidfile();

	/**
	 * @brief get path to log file
	 * @throw YAML::ParserException
	 */
	void get_logfile();


private:
	//! pointer to configuration structure
	static configuration_struct* cfg_;
    //! node that encapsulates YAML information
	YAML::Node config_ = YAML::Node(YAML::NodeType::Map);
};

#endif //CONFIGURATION_MANAGER_H_
