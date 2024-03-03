//
//	request.cpp
//

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>
#include <boost/config.hpp>
#include <algorithm>
#include <cstdlib>
#include <functional>
//#include <iostream>
#include <memory>
//#include <string>
//#include <thread>
//#include <vector>
#include "../include/call_center.hpp"
#include <boost/asio.hpp>
#include <string>
#include "../include/request.hpp"
#include <chrono>
#include <iostream>
#include <random>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <cmath>

using namespace request_call;

request::request(boost::beast::http::request<boost::beast::http::string_body>&& req_str, boost::asio::ip::tcp::socket&& socket)
:stream_(std::move(socket))
{
  
  req_ = req_str;
  date_get_request = boost::posix_time::microsec_clock::local_time();
  call_id = call_id_generator();
  status = "connect";
  std::cout << "call_id: " << call_id << std::endl;
}

int& request::get_call_id()
{
  return call_id;
}

std::string& request::get_request_str()
{
  return request_string;
}

int request::call_id_generator()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    // Определение диапазона для случайного числа
    int minNumber = 1;
    int maxNumber = 100;

    // Генерация случайного числа
    std::uniform_int_distribution<int> distrib(minNumber, maxNumber);
    int random_number = distrib(gen);
  
  return random_number;
}

void request::start_in_queue()
{
  date_in_queue = boost::posix_time::microsec_clock::local_time();

}

boost::posix_time::ptime& request::get_time_in_queue()
{
  return date_in_queue;
}

boost::posix_time::ptime request::get_date_get_request()
{
  return date_get_request;
}

bool request::in_queue_time(int time_in_config)
{
  boost::posix_time::ptime end_time = boost::posix_time::microsec_clock::local_time();
  boost::posix_time::time_duration diff = end_time - date_in_queue;
  double seconds = diff.total_microseconds() / 1e6;
  int duratation = std::round(seconds);

  if (duratation > time_in_config) return false;
  else return true;

}

std::string& request::get_status()
{
  return status;
}

void request::set_status(std::string status_)
{
  status = status_;
}

// void request::fail(boost::beast::error_code ec, char const* what)
// {
//   std::cerr << what << ": " << ec.message() << "\n";
// }
//
//
// void request::run()
// {
//   // We need to be executing within a strand to perform async operations
//   // on the I/O objects in this session. Although not strictly necessary
//   // for single-threaded contexts, this example code is written to be
//   // thread-safe by default.
//   boost::asio::dispatch(stream_.get_executor(),
//                 boost::beast::bind_front_handler(
//                   &request::do_read,
//                   shared_from_this()));
// }
//
// void request::do_read()
// {
//   // Make the request empty before reading,
//   // otherwise the operation behavior is undefined.
//   req_ = {};
//
//   // Set the timeout.
//   stream_.expires_after(std::chrono::seconds(30));
//
//   // Read a request
//   boost::beast::http::async_read(stream_, buffer_, req_,
//                                   boost::beast::bind_front_handler(
//                                     &request::on_read,
//                                     shared_from_this()));
// }
//
// void request::on_read(boost::beast::error_code ec, std::size_t bytes_transferred)
// {
//   boost::ignore_unused(bytes_transferred);
//
//   // This means they closed the connection
//   if(ec == boost::beast::http::error::end_of_stream)
//     return do_close();
//
//   if(ec)
//     return fail(ec, "read");
//   std::cout << req_ << std::endl;
//   // Send the response
//   //do_close();
//   call_center::put_in_queue(this);
//   //send_response(handle_request(*doc_root_, std::move(req_)));
// }
//
// void request::send_response(boost::beast::http::message_generator&& msg)
// {
//   bool keep_alive = msg.keep_alive();
//
//   // Write the response
//   boost::beast::async_write(
//                   stream_,
//                   std::move(msg),
//                   boost::beast::bind_front_handler(
//                     &request::on_write, shared_from_this(), keep_alive));
// }
//
// void request::on_write(bool keep_alive, boost::beast::error_code ec, std::size_t bytes_transferred)
// {
//   boost::ignore_unused(bytes_transferred);
//
//   if(ec)
//     return fail(ec, "write");
//
//   if(! keep_alive)
//   {
//     // This means we should close the connection, usually because
//     // the response indicated the "Connection: close" semantic.
//     return do_close();
//   }
//
//   // Read another request
//   do_read();
// }
//
// void request::do_close()
// {
//   // Send a TCP shutdown
//   boost::beast::error_code ec;
//   stream_.socket().shutdown(boost::asio::ip::tcp::socket::shutdown_send, ec);
//   // At this point the connection is closed gracefully
// }


