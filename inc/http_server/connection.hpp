/**
 * File: connection.hpp
 *
 * Description: Represents a single connection from a client.
 */

#pragma once

#ifndef CONNECTION_H_
#define CONNECTION_H_

#include <array>
#include <boost/asio.hpp>
#include <memory>

namespace http
{
    namespace server
    {

        class connection_manager;

        class connection : public std::enable_shared_from_this<connection>
        {
        public:
            connection(const connection&) = delete;
            connection& operator=(const connection&) = delete;

            /**
             * @brief Construct a connection with the given socket.
             */
            explicit connection(boost::asio::ip::tcp::socket socket, connection_manager& manager);

            /**
             * @brief Start the first asynchronous operation for the connection.
             */
            void start();

            /**
             * @brief Stop all asynchronous operations associated with the connection.
             */
            void stop();

        private:
            /**
             * @brief Perform an asynchronous read operation.
             */
            void do_read();

            /**
             * @brief Perform an asynchronous write operation.
             */
            void do_write(std::size_t bytes_transferred);

            /**
             * @brief Perform an read handler.
             */
            void read_handler(const boost::system::error_code& ec, std::size_t bytes_transferred);

            /**
             * @brief Perform an write handler.
             */
            void write_handler(const boost::system::error_code& ec, std::size_t);

        private:
            //! Socket for the connection.
            boost::asio::ip::tcp::socket socket_;

            //! The manager for this connection.
            connection_manager& connection_manager_;

            //! Buffer for incoming data.
            std::array<char, 8192> buffer_;
        };

        typedef std::shared_ptr<connection> connection_ptr;

    } // namespace server
} // namespace htt

#endif // CONNECTION_H_
