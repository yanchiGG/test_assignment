#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;

int main() 
{
  for(;;)
  {
    try 
    {
      io_service io;

      ;
      ip::tcp::endpoint endpoint(ip::address::from_string("127.0.0.1"), 12345);
      ip::tcp::acceptor acceptor(io, endpoint);
      
      std::cout << "Ожидание подключения..." << std::endl;

      ip::tcp::socket socket(io);
      acceptor.accept(socket);

      boost::asio::streambuf buffer;
      boost::system::error_code error;
      read_until(socket, buffer, "\n", error);
      if (error) 
      {
        throw boost::system::system_error(error);
      }
      
      std::string data(boost::asio::buffer_cast<const char*>(buffer.data()), buffer.size());
      if(data.size() > 2 && std::stoi(data) % 32 == 0)
      {
        std::cout << "Принятые данные:" << data << std::endl;
      }
      else
      {
        std::cout << "Ошибка!"<< std::endl;
      }

      socket.shutdown(ip::tcp::socket::shutdown_both);
      socket.close();
    }

    catch (const std::exception& e) 
    {
      std::cerr << "Ошибка: " << e.what() << std::endl;
    }
  }
  return 0;
}
