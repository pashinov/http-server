/**
 *  File: exception_parser.hpp
 *
 *  Description: Exception messages parser
 */

#pragma once

#ifndef EXCEPTION_PARSER_HPP_
#define EXCEPTION_PARSER_HPP_

#include <string>

#include <exception_type.hpp>
#include <singleton.hpp>

class exception_parser : public singleton<exception_parser>
{
public:
    exception_parser() = default;
    ~exception_parser() = default;

    exception_parser(const exception_parser& copy) = delete;
    exception_parser& operator=(const exception_parser& copy) = delete;

    exception_parser(exception_parser&& copy) = delete;
    exception_parser& operator=(exception_parser&& copy) = delete;

    /**
     * @brief find exception message
     * @return exception message
     */
    const std::string& find_exception_msg(exception_type type) const noexcept;

private:
    //! exception messages
    static const std::string exception_msg_[];
};

#endif //EXCEPTION_PARSER_HPP_
