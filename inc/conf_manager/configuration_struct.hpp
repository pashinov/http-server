/**
 *  File: configuration_struct.hpp
 *
 *  Description: Configuration struct
 *
 */

#ifndef CONFIG_STRUCT_H_
#define CONFIG_STRUCT_H_

#include <string>

//////////////////////////////////////////////////////////////////////////
struct configuration_struct
{
	std::string server_name_;

	struct connection_ep
	{
		std::string ip_address_;
		std::uint16_t port_;
	};

	struct paths
	{
        struct path_pidfile
        {
            std::string pidfile_;
        };

		struct path_logfile
		{
			std::string logfile_;
		};

		path_pidfile pid_;
		path_logfile log_;
	};

	connection_ep connection_ep_;
	paths paths_;
};

#endif // CONFIG_STRUCT_H_
