/**
 *  File: logger.hpp
 *
 *  Description: Generic utility functions
 */

#ifndef UTILITY_H
#define UTILITY_H

#include <string>

/**
* @brief This namespace contains some generic utility functions
*/
namespace utility
{
    /**
     * @brief generate current date and time
     * @return current datatime string (ex. "Thu Nov 23 11:51:50 2017")
     */
    std::string get_date_time(void);
};

#endif // UTILITY_H
