/**
 *  File: logger_exception.hpp
 *
 *  Description: Logger Exception class
 */

#pragma once

#ifndef LOGGER_EXCEPTION_HPP_
#define LOGGER_EXCEPTION_HPP_

#include <string>
#include <exception>

#include <common/exception_type.hpp>

class logger_exception : public std::exception
{
public:
    logger_exception(exception_type type) noexcept;
    ~logger_exception() = default;

    logger_exception(const logger_exception& copy) = default;
    logger_exception& operator=(const logger_exception& copy) = default;

    logger_exception(logger_exception&& copy) = default;
    logger_exception& operator=(logger_exception&& copy) = default;

    /**
     * @brief
     * @return
     */
    const char* what() const noexcept override;

private:
    //!
    std::string msg_;
};

#endif //LOGGER_EXCEPTION_HPP_
