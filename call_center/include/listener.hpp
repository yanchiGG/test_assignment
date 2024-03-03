#pragma once
//#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
//#include <boost/beast/version.hpp>
//#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>
#include <boost/config.hpp>
#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>


class listener : public std::enable_shared_from_this<listener>
{
  boost::asio::io_context& io_context_;
  boost::asio::ip::tcp::acceptor acceptor_;

public:
  listener(boost::asio::io_context& io_context, boost::asio::ip::tcp::endpoint endpoint);

  void run();

private:
  void do_accept();
  
  void on_accept(boost::beast::error_code ec, boost::asio::ip::tcp::socket socket);
  
  void fail(boost::beast::error_code ec, char const* what);
};

 //listener
//------------------------------------------------------------------------------


