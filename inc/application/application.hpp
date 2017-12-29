/**
 * File: application.hpp
 *
 * Description: User application
 */

#pragma once

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <signal.h>

#include <background_application.hpp>

class application : public background_application
{
public:
    application() = default;
    ~application() = default;

    /**
     * @brief main function
     */
    void run() noexcept override;
};

#endif // APPLICATION_H_
