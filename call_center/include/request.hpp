//
//	request.cpp
//

#pragma once
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
//#include <boost/beast/version.hpp>
//#include <boost/asio/dispatch.hpp>
//#include <boost/asio/strand.hpp>
//#include <boost/config.hpp>
//#include <algorithm>
//#include <cstdlib>
//#include <functional>
//#include <iostream>
#include <memory>
//#include <string>
//#include <thread>
//#include <vector>

#include <boost/asio.hpp>
#include <string>
#include <chrono>
#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>

namespace request_call 
{

class request : public std::enable_shared_from_this<request>

{
  private:
    //boost::asio::ip::tcp::socket socket_;
    //boost::asio::ip::tcp::socket socket2;
    std::string request_string;
    std::string status;
    boost::posix_time::ptime date_get_request;
    int call_id;
    boost::beast::tcp_stream stream_; 
    boost::beast::http::request<boost::beast::http::string_body> req_;
    std::string number_abonent;
    boost::posix_time::ptime date_in_queue;
    std::time_t date_end_request;
    std::string status_request;
    std::time_t date_response_operator;
    int id_operator;
    std::time_t call_duration;

  public:
    //void fail(boost::beast::error_code ec, char const* what);

    request(boost::beast::http::request<boost::beast::http::string_body>&& req_str, boost::asio::ip::tcp::socket&& socket);
    // 
    // void run();
    // 
    // void do_read(); 
    //
    // void on_read(boost::beast::error_code ec, std::size_t bytes_transferred);
    // 
    // void send_response(boost::beast::http::message_generator&& msg);
    // 
    // void on_write(bool keep_alive, boost::beast::error_code ec, std::size_t bytes_transferred);
    //
    // void do_close();

//void send(std::string& response);

    int& get_call_id();

    void start_in_queue();

    boost::posix_time::ptime& get_time_in_queue();
//boost::asio::ip::tcp::socket& get_socket();

    std::string& get_request_str();

    boost::posix_time::ptime get_date_get_request();
  
    bool in_queue_time(int time_in_config);
   
    // void sent_operator();

	  int call_id_generator();

    std::string& get_status();
    
    void set_status(std::string status_);

};

} //request_call
