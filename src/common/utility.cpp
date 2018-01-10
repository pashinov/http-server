#include <iomanip>

#include <configuration_manager.hpp>
#include <logger.hpp>
#include <logger_exception.hpp>
#include <utility.hpp>

std::string utility::get_date_time(void)
{
    std::stringstream datetime;
    std::time_t t = std::time(nullptr);
    datetime << std::put_time(std::localtime(&t), "%a %b %d %H:%M:%S %Y");

    return datetime.str();
}

void utility::initialization_config(std::string filename)
{
    try
    {
        configuration_manager::instance_ptr()->load_config_file(filename);
    }
    catch(YAML::Exception &ex)
    {
        throw ex;
    }
}

void utility::initialization_logger(std::string filename)
{
    try
    {
        logger::instance_ptr()->init_log_file(level::info, filename);
        logger::instance_ptr()->log(level::info, "Logfile initialization complete");
    }
    catch (logger_exception& ex)
    {
        throw ex;
    }
}
