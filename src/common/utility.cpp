#include <iomanip>

#include <utility.hpp>

//////////////////////////////////////////////////////////////////////////
std::string utility::get_date_time(void)
{
    std::stringstream datetime;
    std::time_t t = std::time(nullptr);
    datetime << std::put_time(std::localtime(&t), "%a %b %d %H:%M:%S %Y");

    return datetime.str();
}
