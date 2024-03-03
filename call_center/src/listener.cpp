
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>
#include <boost/config.hpp>
#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include "../include/request.hpp"
#include "../include/listener.hpp"
#include "../include/queue_request.hpp"
#include "../include/session.hpp"

void listener::fail(boost::beast::error_code ec, char const* what)
{
  std::cerr << what << ": " << ec.message() << "\n";
}

listener::listener(boost::asio::io_context& io_context, boost::asio::ip::tcp::endpoint endpoint)
  : io_context_(io_context), acceptor_(boost::asio::make_strand(io_context))
{
  boost::beast::error_code ec;
  
  // Open the acceptor
  acceptor_.open(endpoint.protocol(), ec);
  if(ec)
  {
    fail(ec, "open");
    return;
  }

  // Allow address reuse
  acceptor_.set_option(boost::asio::socket_base::reuse_address(true), ec);
  if(ec)
  {
    fail(ec, "set_option");
    return;
  }

  // Bind to the server address
  acceptor_.bind(endpoint, ec);
  if(ec)
  {
    fail(ec, "bind");
    return;
  }

  // Start listening for connections
  acceptor_.listen(boost::asio::socket_base::max_listen_connections, ec);
  
  if(ec)
  {
    fail(ec, "listen");
    return;
  }
}

void listener::run()
{
  do_accept();
}

void listener::do_accept()
{
  //The new connection gets its own strand
  acceptor_.async_accept(
              boost::asio::make_strand(io_context_),
              boost::beast::bind_front_handler(
                &listener::on_accept,
                shared_from_this()));
}

void listener::on_accept(boost::beast::error_code ec, boost::asio::ip::tcp::socket socket)
{
  if(ec)
  {
    fail(ec, "accept");
    return; // To avoid infinite l
  }
  else
  {
    // Create the session and run it
    std::make_shared<session>(std::move(socket))-> run();
  }

  // Accept another connection
  do_accept();
}



