/**
 * File: connection_manager.hpp
 *
 * Description: Manages open connections so that they may be cleanly stopped when the server
 * needs to shut down.
 */

#pragma once

#ifndef CONNECTION_MANAGER_H_
#define CONNECTION_MANAGER_H_

#include <set>

#include <connection.hpp>

namespace http
{
    namespace server
    {

        class connection_manager
        {
        public:
            connection_manager(const connection_manager&) = delete;
            connection_manager& operator=(const connection_manager&) = delete;

            /**
             * @brief Construct a connection manager.
             */
            connection_manager();

            /**
             * @brief Add the specified connection to the manager and start it.
             */
            void start(connection_ptr c);

            /**
             * @brief Stop the specified connection.
             */
            void stop(connection_ptr c);

            /**
             * @brief Stop all connections.
             */
            void stop_all();

        private:
            //! The managed connections.
            std::set<connection_ptr> connections_;
        };

    } // namespace server
} // namespace http

#endif //CONNECTION_MANAGER_H_
