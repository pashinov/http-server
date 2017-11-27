#include <cassert>

#include <configuration_manager.hpp>

configuration_struct* configuration_manager::cfg_ = nullptr;

configuration_manager::configuration_manager()
{
	if(cfg_ == nullptr)
	{
		cfg_ = new configuration_struct();
	}
}

configuration_manager::~configuration_manager()
{
	if(cfg_)
	{
		delete cfg_;
	}
}

void configuration_manager::load_config_file(std::string filename)
{
	assert(!filename.empty());

	config_ = YAML::LoadFile(filename);
	assert(config_.IsMap());

	try
	{
		get_server_name();
		get_ip_address();
		get_port();
        get_pidfile();
        get_logfile();
	}
	catch(YAML::ParserException &ex)
	{
		throw ex;
	}
}

const configuration_struct* configuration_manager::get_config() noexcept
{
	return cfg_;
}

void configuration_manager::get_server_name()
{
	try
	{
		cfg_->server_name_ = config_["Server"]["Name"].as<std::string>();
	}
	catch(YAML::ParserException& ex)
	{
		throw ex;
	}
}

void configuration_manager::get_ip_address()
{
	try
	{
		cfg_->connection_ep_.ip_address_ = config_["Server"]["Connection endpiont"]["ip_addr"].as<std::string>();
	}
	catch(YAML::ParserException& ex)
	{
		throw ex;
	}
}

void configuration_manager::get_port()
{
	try
	{
		cfg_->connection_ep_.port_ = config_["Server"]["Connection endpiont"]["port"].as<std::uint16_t>();
	}
	catch(YAML::ParserException& ex)
	{
		throw ex;
	}
}

void configuration_manager::get_pidfile()
{
    try
    {
        cfg_->paths_.pid_.pidfile_ = config_["Server"]["Paths"]["Pid"]["pidfile"].as<std::string>();
    }
    catch(YAML::ParserException& ex)
    {
        throw ex;
    }
}

void configuration_manager::get_logfile()
{
	try
	{
		cfg_->paths_.log_.logfile_ = config_["Server"]["Paths"]["Log"]["logfile"].as<std::string>();
	}
	catch(YAML::ParserException& ex)
	{
		throw ex;
	}
}
