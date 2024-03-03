//
//  session.cpp
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
#include <iostream>
#include <memory>
#include "../include/request.hpp"
//#include "../include/listener.hpp"
#include "../include/queue_request.hpp"
#include "../include/session.hpp"
#include "../include/config.hpp"
#include <mutex>
#include <boost/date_time/posix_time/posix_time.hpp>

extern config configuration;

template <class Body, class Allocator>
boost::beast::http::message_generator
handle_request(boost::beast::http::request<Body, boost::beast::http::basic_fields<Allocator>>&& req, int status)
{

    // Returns a bad request response
    // auto const bad_request =
    // [&req](boost::beast::string_view why)
    // {
  if (status == 0)
  {    
    boost::beast::http::response<boost::beast::http::string_body> res{boost::beast::http::status::ok, req.version()};
        
    res.set(boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(boost::beast::http::field::content_type, "text");
    res.body() = "Queue full!";
    res.keep_alive(false);
    //res.body() = std::string(boost::beast::string_view why);
    res.prepare_payload();
    return res;
  }

  if (status == 1)
  {    
    boost::beast::http::response<boost::beast::http::string_body> res{boost::beast::http::status::bad_request, req.version()};
        
    res.set(boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(boost::beast::http::field::content_type, "text");
    res.body() = "Already in queue!";
    res.keep_alive(false);
    //res.body() = std::string(boost::beast::string_view why);
    res.prepare_payload();
    return res;
  }

  if (status == 2)
  {    
    boost::beast::http::response<boost::beast::http::string_body> res{boost::beast::http::status::ok, req.version()};
        
    res.set(boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(boost::beast::http::field::content_type, "text");
    res.body() = "Timeout";
    res.keep_alive(false);
    //res.body() = std::string(boost::beast::string_view why);
    res.prepare_payload();
    return res;
  }
  if (status == 3)
  {    
    boost::beast::http::response<boost::beast::http::string_body> res{boost::beast::http::status::ok, req.version()};
        
    res.set(boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(boost::beast::http::field::content_type, "text");
    res.body() = "waiting!";
    res.keep_alive(true);
    //res.body() = std::string(boost::beast::string_view why);
    res.prepare_payload();
    return res;
  }

}

session::session(boost::asio::ip::tcp::socket&& socket)
  : stream_(std::move(socket))
{
  lenght_queue = configuration.config::get_config("lenght_queue");
  time_in_queue = configuration.config::get_config("time_in_queue");
  count_operator = configuration.config::get_config("count_operator");


  status = 0;

  boost::asio::socket_base::keep_alive option(true);
  stream_.socket().set_option(option);

  request_ = std::make_shared<request_call::request>(std::move(req_), std::move(socket));

}


void session::fail(boost::beast::error_code ec, char const* what)
{
  std::cerr << what << ": " << ec.message() << "\n";
}

void session::run()
{
  // We need to be executing within a strand to perform async operations
  // on the I/O objects in this session. Although not strictly necessary
  // for single-threaded contexts, this example code is written to be
  // thread-safe by default.
  boost::asio::dispatch(stream_.get_executor(),
                boost::beast::bind_front_handler(
                  &session::do_read,
                  shared_from_this()));
}

void session::do_read()
{
  // Make the request empty before reading,
  // otherwise the operation behavior is undefined.
  req_ = {};
 //  std::lock_guard<std::mutex> lock(data_mutex_);
  // Set the timeout.
  //  std::chrono::seconds time(time_in_queue);
  // boost::system::error_code ec;
  // stream_.socket().expires_at(std::chrono::steady_clock::now() + time, ec);  
  // if (ec)
  // {
  // send_response(handle_request(std::move(req_), 2));
  // }
  // std::lock_guard<std::mutex> lock(data_mutex_);
  // Read a request

  boost::beast::http::async_read(stream_, buffer_, req_,
                                  boost::beast::bind_front_handler(
                                    &session::on_read,
                                    shared_from_this()));
  
 
}

void session::on_read(boost::beast::error_code ec, std::size_t bytes_transferred)
{
  boost::ignore_unused(bytes_transferred);

  // This means they closed the connection
  if(ec == boost::beast::http::error::end_of_stream)
    return do_close();
  if(ec)
    return fail(ec, "read");

  std::string number_ = req_.target();
  number_.erase(number_.begin());
  number = std::stoi(number_);

  std::cout << number << std::endl;

  queue_request::write();
  
  if (queue_request::in_queue(number))
  send_response(handle_request(std::move(req_), 1));// status = "already_in_queue"
  else if(queue_request::get_size_queue() >= lenght_queue)
        send_response(handle_request(std::move(req_), 0)); // status = "queue_is_full"
      else 
        queue_request::put_in_queue(number, request_);

  // auto result = std::async(on_do);
  // int flag = result.get();
  on_do();
  //do_read();
 }

void session::on_wait(const boost::system::error_code&/* , request_call::request&& request_ */)
{
  send_response(handle_request(std::move(req_), 2)); // status = "timeout"
}

void session::send_response(boost::beast::http::message_generator&& msg)
{
  bool keep_alive = msg.keep_alive();

  //std::lock_guard<std::mutex> lock(data_mutex_);
  // std::lock_guard<std::mutex> lock(data_mutex_);
  // Write the response
  boost::beast::async_write(
                  stream_,
                  std::move(msg),
                  boost::beast::bind_front_handler(
                    &session::on_write, shared_from_this(), keep_alive));
}

void session::on_write(bool keep_alive, boost::beast::error_code ec, std::size_t bytes_transferred)
{
  boost::ignore_unused(bytes_transferred);
  if(ec)
    return fail(ec, "write");
  
  if(! keep_alive)
  {
    // This means we should close the connection, usually because
    // the response indicated the "Connection: close" semantic.
    return do_close();
  }

  // Read another request]
  // do_read();
}

void session::do_close()
{
  // Send a TCP shutdown
  boost::beast::error_code ec;
    stream_.socket().shutdown(boost::asio::ip::tcp::socket::shutdown_send, ec);
  // At this point the connection is closed gracefully
}

void session::on_do()
{}
  //  if(free_operators > 0 && queue_request::first_in_queue() == number ) 
  // {
  //   free_operators--;
  //   queue_request::get_of_queue();
  //   boost::asio::io_service io;
  //   boost::asio::deadline_timer timer(io, boost::posix_time::seconds(9));
  //   timer.async_wait(std::bind(&session::on_wait, shared_from_this(),  std::placeholders::_1));
  //   io.run();
  // }}
//   std::condition_variable cv;
//   std::mutex mtx;
//   bool isEventOccurred = false;
//   
//   std::thread eventThread(waitForEvent);
//   notifyEvent();
//   eventThread.join();
//
//   }
// void session::waitForEvent() {
//     std::unique_lock<std::mutex> lock(mtx);
//     cv.wait(lock, []{ return isEventOccurred; });
//     // Выполнение кода после возникновения события
//     std::cout << "Событие произошло!" << std::endl;
// }
//
// void session::notifyEvent() {
//     std::this_thread::sleep_for(std::chrono::seconds(3)); // Имитация возникновения события через 3 секунды
//     std::lock_guard<std::mutex> lock(mtx);
//     isEventOccurred = true;
//     cv.notify_one();
// }

int	session::free_operators = configuration.config::get_config("count_operator");

