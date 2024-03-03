//
//		call_center.hpp
//

#pragma once

#include <iostream>
#include <queue>
#include <map>
#include <string>
#include "../include/request.hpp"
#include <boost/asio.hpp>

class call_center
{
	private:
		boost::asio::io_context io_context;
		//std::queue <int> queue_call_id;
		//std::map <int, request_call::request*> request_base;
		int lenght_queue;
		int count_operator;
		int free_operators;

	public:
	
	call_center ();

	void get_request(boost::asio::io_context& io_context, unsigned short port);
	
	static void put_in_queue(request_call::request* request_n);
	
	int get_of_queue();

	void start_server(boost::asio::io_context& io_context, boost::asio::ip::address address, unsigned short port);
	
	std::string& send_to_opertor(int call_id, std::string& request_str);

	void send_response();

	void response_primary(request_call::request* request_, int response_code);

	void send_wait_response();

	void distribute_request_operator();
};
