/**
 *  File: logger.hpp
 *
 *  Description: Generic utility functions
 */

#pragma once

#ifndef UTILITY_HPP_
#define UTILITY_HPP_

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

    /**
     * @brief initialization configuration file
     * @throw YAML::Exception
     */
    void initialization_config(std::string filename);

    /**
     * @brief initialization log file
     * @throw logger_exception
     */
    void initialization_logger(std::string filename);
}

#endif //UTILITY_HPP_
