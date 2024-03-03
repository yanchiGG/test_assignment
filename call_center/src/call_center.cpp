//
//	call_center.cpp
//

#include "../include/call_center.hpp"
#include <iostream>
#include "../include/config.hpp"
#include <boost/asio.hpp>
#include "../include/request.hpp"
#include <cstdlib>
#include <memory>
#include <ctime>
#include "../include/listener.hpp"
#include "../include/queue_request.hpp"
extern config configuration;

call_center::call_center()
{	
	//lenght_queue = configuration.config::get_config("lenght_queue");
	count_operator = configuration.config::get_config("count_operator");
	free_operators = count_operator;
}

void call_center::start_server(boost::asio::io_context& io_context, boost::asio::ip::address address, unsigned short port) 
{
	std::shared_ptr<listener> list = std::make_shared<listener>(io_context, boost::asio::ip::tcp::endpoint{address, port});
	bool flag = false;
	for(;;)
	{
		if(flag == false)
		{
			list -> run();
			flag = true;
		}
		
		//std::cout << "+";
		// if(free_operators > 0 && queue_request::get_size_queue() != 0)
		// 	{
		// 		free_operators--;
		// 		queue_request::get_of_queue();
		// 	}
	}
	
	//std::cout << "uikqewhdlkjshdkajhsdkjhas" << std::endl;
    //get_request(io_context, port);
	// for(;;)
	// {
	//if(queue_request::get_size_queue() > 0) 
	//std::cout<<"lkdhdjhf";//std::cout << queue_request::get_of_queue() -> get_call_id();
	// 	//send_wait_response();
	//
	// 	//std::cout << "lol"<< std::endl << request_base.at(queue_call_id.front()) -> get_request_str();
	// 	//distribute_request_operator();
	//
	// }
	//
	// io_context.run();
}

// void call_center::get_request(boost::asio::io_context& io_context, unsigned short port) 
// {
// 	if(queue_call_id.size() < lenght_queue)
// 	{
// 		// boost::asio::streambuf request;
// 		// boost::asio::read_until(socket, request, "\r\n\r\n");
// 		// std::cout << "HTTP запрос:\n" << boost::asio::buffer_cast<const char*>(request.data()) << std::endl;
//   	// Прочитать и обработать содержимое запроса HTTP
// 		// std::string request_str = boost::asio::buffer_cast<const char*>(request.data());
// 		request_call::request* request_new = new request_call::request(io_context, port);
// 	
// 		put_in_queue(request_new);
// 	}
// 	// else
// 	// {
// 	// 	response_primary(request_new.get_socket(), 2);
// 	// }
// }
//
// void call_center::put_in_queue(request_call::request* request_n)
// {
// 	//request_base.insert(std::pair<int, request_call::request>(request_n.get_call_id(), request_n));
// 	request_base[request_n -> get_call_id()] = request_n;
// 	queue_call_id.push(request_n -> get_call_id());
// 	//response_primary(request_n, 0);
// 	//response_primary(request_n, 0);
//
// 		std::cout << "-----------------------------" << std::endl
// 		<< "size_queue: " << queue_call_id.size() << std::endl 
// 		<< "lenght_queue: " << lenght_queue << std::endl 
// 		<< "call_id: " << request_n -> get_call_id() << std::endl
// 		<<"free_operators: " << free_operators << std::endl
// 		<< "-----------------------------" << std::endl
// 		<< "request string: " << std::endl << request_n -> get_request_str() <<std::endl
// 		<< "-----------------------------" << std::endl;
// 		//<< std::ctime(request_n -> get_date_get_request()) << std::endl;
// }
// 	
// int call_center::get_of_queue()
// {
// 	std::cout << "free_operators: " << free_operators << std::endl;
// 	if(!queue_call_id.empty())
// 	{
// 		int front_call_id = queue_call_id.front();
// 		queue_call_id.pop();
// 		return front_call_id;
// 	}
// else 
// 	{
// 		return 0;
// 	}
// }
//
// void send_response()
// {
//
// }

//
// void call_center::response_primary(request_call::request* request_, int response_code)
// {
// 	std::string response;
// 	switch(response_code)
// 	{
// 		case 0: response =
//     	"HTTP/1.1 202 OK\r\n"
// 			"Content-Type: text/plain\r\n"
// 			"Content-Length: 51\r\n"
// 			"Connection: keep-alive\r\n"
//     	"\r\n"
//     	"Your call has been accepted and is being processed.\r\n";
//     	//"\r\n\r\n";
//       break;
//
// 		case 1: response =
//       "HTTP/1.1 202 OK\r\n"
//       "Content-Length: 40\r\n"
//       "Content-Type: text/plain\r\n"
//       "\r\n"
//       "Your call is already in queue.\r\n";
// 			break;
//
// 		case 2: response =
//     	"HTTP/1.1 200 OK\r\n"
//       "Content-Length: 28\r\n"
//       "Content-Type: text/plain\r\n"
//       "\r\n"
//       "The queue is full.\r\n";
// 			break;
// 	}
// 			
//   //boost::asio::write(socket, boost::asio::buffer(response));
// 	request_ -> send(response);
// }
// 	
// void call_center::distribute_request_operator()
// {
// 	while(free_operators > 0 && !queue_call_id.empty())
// 	{
// 		//request_call::request request_to_send = get_of_queue();
// 		int code = get_of_queue();
// 		if(code != 0) 
// 		{
// 			//request_call::request& request_to_send = request_base.at(code);
// 			//free_operators--;
// 		}
// 		else {}
// 	}
// }

// void call_center::send_wait_response()
// {
// 	std::string response_wait = 
// 		"HTTP/1.1 202 OK\r\n"
//     "Content-Length: 7\r\n"
// 		"Connection: keep-alive\r\n"
//     "Content-Type: text/plain\r\n"
//     "\r\n"
//     "Waiting\r\n";
// //		request_base(queue_call_id.front()).get_socket()
//
// 		request_base.at(queue_call_id.front()) -> send(response_wait);
//
// }
