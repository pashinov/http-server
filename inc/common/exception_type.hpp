/**
 *  File: exception_type.hpp
 *
 *  Description: Exception types
 */

#pragma once

#ifndef EXCEPTION_TYPE_HPP_
#define EXCEPTION_TYPE_HPP_

enum exception_type
{
	logger_init = 0,
    logger_write,
    logger_clear,

	exception_type_end
};

#endif //EXCEPTION_TYPE_HPP_
