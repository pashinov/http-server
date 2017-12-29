#include <connection.hpp>
#include <connection_manager.hpp>

namespace http
{
    namespace server
    {
        connection::connection(boost::asio::ip::tcp::socket socket, connection_manager& manager)
                : socket_(std::move(socket)),
                  connection_manager_(manager)
        {

        }

        void connection::start()
        {
            do_read();
        }

        void connection::stop()
        {
            socket_.close();
        }

        void connection::do_read()
        {
            socket_.async_read_some(boost::asio::buffer(buffer_), std::bind(&connection::read_handler,
                                                                            shared_from_this(),
                                                                            std::placeholders::_1,
                                                                            std::placeholders::_2));
        }

        void connection::read_handler(const boost::system::error_code& ec, std::size_t bytes_transferred)
        {
            if (!ec)
            {
                do_write(bytes_transferred);
            }
            else if (ec != boost::asio::error::operation_aborted)
            {
                connection_manager_.stop(shared_from_this());
            }
        }

        void connection::do_write(std::size_t bytes_for_transfer)
        {
            boost::asio::async_write(socket_,
                                     boost::asio::buffer(buffer_, bytes_for_transfer),
                                     std::bind(&connection::write_handler,
                                               shared_from_this(),
                                               std::placeholders::_1,
                                               std::placeholders::_2));
        }

        void connection::write_handler(const boost::system::error_code& ec, std::size_t)
        {
            if (!ec)
            {
                // Initiate graceful connection closure.
                boost::system::error_code ignored_ec;
                socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both,
                                 ignored_ec);
            }

            if (ec != boost::asio::error::operation_aborted)
            {
                connection_manager_.stop(shared_from_this());
            }
        }

    } // namespace server
} // namespace http
