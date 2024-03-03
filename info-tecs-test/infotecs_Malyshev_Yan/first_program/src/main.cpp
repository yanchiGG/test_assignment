#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <algorithm>
#include <boost/asio.hpp>
#include "../include/buffer.hpp"

using namespace boost::asio;

void first_thread(buff* buf_);

void second_thread(buff* buf_);

void insertion_sort(std::string& str);

int main()
{
  buff public_buffer;
  std::thread first(first_thread, &public_buffer);
  std::thread second(second_thread, &public_buffer);
  
  first.join();
  second.join();
}

void first_thread(buff* buf_)
{
  for(;;)
  {
    std::string input_str = "";

    std::cin >> input_str;

    if(input_str.size() < 1)
    {
      std::cout << "Вы ввели пустую строку!" << std::endl;
      continue;
    }

    if(input_str.size() > 64)
    {
      std::cout << "Строка превышает допустимый размер!" << std::endl;
      continue;
    }
    
    bool is_letter = false;

    for(int i = 0; i < input_str.size(); i++)
    {
      if(!std::isdigit(input_str[i]))
      {
        is_letter = true;
        break;
      }
    }

    if(is_letter)
    {
      std::cout << "Строка состоит не только из цифр!" << std::endl;
      continue;
    }
    
    insertion_sort(input_str);
    
    for(int i = 0; i < input_str.size(); i++)
    {
      if((input_str[i] - '0') % 2 == 0)
        {
          input_str.erase(i, 1);
          input_str.insert(i, "KB");
          i++;
        }
    }
    
    buf_ -> set_data(input_str);
  }
}

void second_thread(buff* buf_)
{
  for(;;)
  {
    bool data_ready = false;
    std::string data = buf_ -> get_data();
    
    std::cout << data << std::endl;
    data_ready = true;
    int sum_digit = 0;

    if(data_ready)
    {
      for(int i = 0; i < data.size(); i++)
      {
        if(std::isdigit(data[i]))
        {
          sum_digit += data[i] - '0';
        }
      }
    }

    try 
    {
      io_service io;

      ip::tcp::socket socket(io);

      ip::tcp::endpoint endpoint(ip::address::from_string("127.0.0.1"), 12345);

      socket.connect(endpoint);

      std::string message = "";
      message = std::to_string(sum_digit) + "\n";

      boost::system::error_code error;
      write(socket, buffer(message), error);
      if (error) 
      {
          throw boost::system::system_error(error);
      }

      socket.shutdown(ip::tcp::socket::shutdown_both);
      socket.close();
    } 
    catch (const std::exception& e)
    {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
    
    data_ready = false;
  }
}

void insertion_sort(std::string& str) {
    for (size_t i = 1; i < str.length(); i++) {
        char key = str[i];
        int j = i - 1;
        while (j >= 0 && str[j] < key) {
            str[j + 1] = str[j];
            j--;
        }
        str[j + 1] = key;
    }
}
