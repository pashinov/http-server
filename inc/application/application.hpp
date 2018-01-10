/**
 * File: application.hpp
 *
 * Description: User application
 */

#pragma once

#ifndef APPLICATION_HPP_
#define APPLICATION_HPP_

#include <signal.h>

#include <background_application.hpp>

class application : public background_application
{
public:
    application() = default;
    ~application() = default;

    application(const application& copy) = delete;
    application& operator=(const application& copy) = delete;

    application(application&& copy) = delete;
    application& operator=(application&& copy) = delete;

    /**
     * @brief main function
     */
    void run() noexcept override;
};

#endif //APPLICATION_HPP_
