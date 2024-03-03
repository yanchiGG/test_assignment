//
//  session.hpp
//

#pragma once
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
#include <mutex>
#include <string>

class session : public std::enable_shared_from_this<session>
{
    boost::beast::tcp_stream stream_;
    boost::beast::flat_buffer buffer_;
    //std::shared_ptr<std::string const> doc_root_;
    boost::beast::http::request<boost::beast::http::string_body> req_;
    int time_in_queue;
    std::mutex data_mutex_;
    int number;
    int status;
    int lenght_queue;
	int count_operator;
    static int free_operators;

    std::shared_ptr<request_call::request> request_;

public:
    // Take ownership of the stream
    session(boost::asio::ip::tcp::socket&& socket);

    void run();
    
    void do_read(); 
    
    
    void on_do();
    
    void on_wait(const boost::system::error_code& /* , request_call::request&& request_ */);

    void on_read(boost::beast::error_code ec, std::size_t bytes_transferred);
    void send_response(boost::beast::http::message_generator&& msg);
    
    void on_write(bool keep_alive, boost::beast::error_code ec, std::size_t bytes_transferred);

    void do_close();

    void fail(boost::beast::error_code ec, char const* what);
    
    // template <class Body, class Allocator>
    // boost::beast::http::message_generator 
    //boost::beast::http::message<boost::beast::http::string_body, boost::beast::http::basic_fields<>> handle_request();
    //boost::beast::http::string_body handle_request();

};           
