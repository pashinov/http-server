#include <exception_parser.hpp>
#include <logger_exception.hpp>

logger_exception::logger_exception(exception_type type) noexcept :
        msg_(exception_parser::instance_ptr()->find_exception_msg(type))
{

}

const char* logger_exception::what() const noexcept
{
    std::string msg = "logger: " + msg_;
	return msg.c_str();
}
