#include <common/exception_parser.hpp>

#include <cassert>

const std::string& exception_parser::find_exception_msg(exception_type type) const noexcept
{
    assert(type < exception_type::exception_type_end);

    return exception_msg_[type];
}

const std::string exception_parser::exception_msg_[] = {
        "Error initializing logfile",
        "Error writing to logfile",
        "Error cleaning logfile"
};
