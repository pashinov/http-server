/**
 * File: server.hpp
 *
 * Description: The top-level class of the HTTP server.
 */

#pragma once

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <boost/asio.hpp>
#include <string>

#include <connection.hpp>
#include <connection_manager.hpp>
#include <request_handler.hpp>

namespace http
{
    namespace server
    {

        class server
        {
        public:
            server(const server&) = delete;
            server& operator=(const server&) = delete;

            /**
             * @brief Construct the server to listen on the specified TCP address and port, and
             * serve up files from the given directory.
             */
            explicit server(const std::string& address, const std::string& port, const std::string& doc_root);

            /**
             * @brief Run the server's io_service loop.
             */
            void run();

        private:
            /**
             * @brief Perform an asynchronous accept operation.
             */
            void do_accept();

            /**
             * @brief Perform an accept handler.
             */
            void accept_handler(const boost::system::error_code& error);

        private:
            //! The io_service used to perform asynchronous operations.
            boost::asio::io_service io_service_;

            //! Acceptor used to listen for incoming connections.
            boost::asio::ip::tcp::acceptor acceptor_;

            //! The next socket to be accepted.
            boost::asio::ip::tcp::socket socket_;

            //! The connection manager which owns all live connections.
            connection_manager connection_manager_;

            //! The handler for all incoming requests.
            request_handler request_handler_;
        };

    } // namespace server
} // namespace http

#endif //SERVER_HPP_
