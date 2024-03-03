#include <iostream>
#include <string>
#include "../include/config.hpp"
#include "../include/call_center.hpp"
#include <boost/asio.hpp>
#include <memory>
#include <thread>
#include <vector>
#include <cstdlib>
#include "../include/listener.hpp"

config configuration;

int main(int argc, char* argv[])
{
  // Check command line arguments.
  if (argc != 4)
  {
  	std::cerr <<
      "Usage: http-server-async <address> <port> <threads>\n" <<
      "Example:\n" <<
      "    http-server-async 0.0.0.0 8080 1\n";
    return EXIT_FAILURE;
  }
  auto const address = boost::asio::ip::make_address(argv[1]);
	auto const port = static_cast<unsigned short>(std::atoi(argv[2]));
  auto const threads = std::max<int>(1, std::atoi(argv[3]));

  // The io_context is required for all I/O
  boost::asio::io_context io_context{threads};

  // Create and launch a listening port
/*   std::make_shared<listener>(io_context, boost::asio::ip::tcp::endpoint{address, port})->run(); */

	call_center main_server;
	main_server.start_server(io_context, address, port);
	//boost::asio::io_service io_service;

//	main_server.start_server(8080);
	//io_service.run();

  // Run the I/O service on the requested number of threads
  std::vector<std::thread> v;
  v.reserve(threads - 1);

  for(auto i = threads - 1; i > 0; --i)
    v.emplace_back( [&io_context] { io_context.run(); });
  io_context.run();

  return EXIT_SUCCESS;
}

