#include <utility>

#include <server.hpp>

namespace http
{
    namespace server
    {

        server::server(const std::string& address, const std::string& port, const std::string& doc_root)
                : io_service_(),
                  acceptor_(io_service_),
                  connection_manager_(),
                  socket_(io_service_),
                  request_handler_(doc_root)
        {
            // Open the acceptor with the option to reuse the address (i.e. SO_REUSEADDR).
            boost::asio::ip::tcp::resolver resolver(io_service_);
            boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve({address, port});
            acceptor_.open(endpoint.protocol());
            acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
            acceptor_.bind(endpoint);
            acceptor_.listen();

            do_accept();
        }

        void server::run()
        {
            // The io_service::run() call will block until all asynchronous operations
            // have finished. While the server is running, there is always at least one
            // asynchronous operation outstanding: the asynchronous accept call waiting
            // for new incoming connections.
            io_service_.run();
        }

        void server::do_accept()
        {
            acceptor_.async_accept(socket_, std::bind(&server::accept_handler,
                                                      this,
                                                      std::placeholders::_1));
        }

        void server::accept_handler(const boost::system::error_code& ec)
        {
            // Check whether the server was stopped by a signal before this
            // completion handler had a chance to run.
            if (!acceptor_.is_open())
            {
                return;
            }

            if (!ec)
            {
                connection_manager_.start(std::make_shared<connection>(std::move(socket_), connection_manager_, request_handler_));
            }

            do_accept();
        }

    } // namespace server
} // namespace http
