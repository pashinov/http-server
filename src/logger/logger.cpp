#include <fstream>

#include <logger.hpp>
#include <utility.hpp>

//////////////////////////////////////////////////////////////////////////
logger::logger() : level_filter_(level::normal)
{

}

//////////////////////////////////////////////////////////////////////////
void logger::init_log_file(std::string filename)
{
    assert(!filename.empty());

    filename_ = filename;

    logger::clear_log_file();

    if (this->push(level_filter_, "Logfile initialization complete"))
    {
        throw; //TODO:
    }
}

//////////////////////////////////////////////////////////////////////////
void logger::init_log_file(level log_level, std::string filename)
{
    assert(!filename.empty());

    filename_ = filename;
    level_filter_ = log_level;

    logger::clear_log_file();

    if (this->push(level_filter_, "Logfile initialization complete"))
    {
        throw; //TODO:
    }
}

//////////////////////////////////////////////////////////////////////////
void logger::set_log_level(level log_level) noexcept
{
    level_filter_ = log_level;
}

//////////////////////////////////////////////////////////////////////////
void logger::log(std::string message) const
{
    if (this->push(level_filter_, message))
    {
        throw; //TODO:
    }
}

//////////////////////////////////////////////////////////////////////////
void logger::log(level log_level, std::string message) const
{
    if (log_level >= level_filter_)
    {
        if (this->push(log_level, message))
        {
            throw; //TODO:
        }
    }
}

//////////////////////////////////////////////////////////////////////////
void logger::clear_log_file() const
{
    if (!filename_.empty())
    {
        std::ofstream stream;
        {
            std::lock_guard<std::mutex> guard(mutex_log_);
            stream.open(filename_,  std::ios::out | std::ios::trunc);
            if(!stream.is_open())
            {
                throw; //TODO:
            }
            stream.close();
        }
    }
}

bool logger::push(level log_level, std::string message) const noexcept
{
    assert(!message.empty());

    std::string full_message = this->print(log_level, message);

    std::ofstream stream;
    {
        std::lock_guard<std::mutex> guard(mutex_log_);
        stream.open(filename_, std::ios::out | std::ios::app);
        if(!stream.is_open()) {return true;}
        stream.write(full_message.c_str(), full_message.size());
        stream.close();
    }

    return false;
}

//////////////////////////////////////////////////////////////////////////
std::string logger::print(level level, std::string message) const noexcept
{
    std::string datetime = utility::get_date_time();

    std::string lvl;
    switch (level)
    {
        case level::debug:
            lvl = "DEBUG";
            break;
        case level::verbose:
            lvl = "VERBOSE";
            break;
        case level::info:
            lvl = "INFO";
            break;
        case level::normal:
            lvl = "NORMAL";
            break;
        case level::warning:
            lvl = "WARNING";
            break;
        case level::error:
            lvl = "ERROR";
            break;
        default:
            lvl = "---";
            break;
    }

    return datetime + " - " + lvl + " : " + message + "\n";
}
