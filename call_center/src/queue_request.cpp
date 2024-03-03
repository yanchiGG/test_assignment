#include <map>
#include <queue>
#include <memory>
#include "../include/queue_request.hpp"
#include "../include/request.hpp"

void queue_request::put_in_queue(int number, std::shared_ptr<request_call::request> req) 
{
  req -> set_status("in_queue");
  request_queue.push_back(number);
  request_map[number] = req;
  req -> start_in_queue();
}

void queue_request::get_of_queue() 
{
  int id = request_queue.front();
  std::shared_ptr<request_call::request> req = request_map[id];
  request_queue.erase(request_queue.begin());
  request_map.erase(id);
}

bool queue_request::in_queue(int number)
{
  bool flag = false;
  for(auto i = request_queue.begin(); i != request_queue.end(); i++ )
  {
    if (*i == number)
    {
      flag = true;
      break;
    }
  }
  return flag;
}

int queue_request::get_size_queue()
{
  return request_queue.size();
}

void queue_request::write()
{
  std::cout << "Длина очереди: " <<request_queue.size() << std::endl << std::endl;
}

int queue_request::first_in_queue()
{
  return request_queue.front();
}

std::list<int> queue_request::request_queue;

std::map<int, std::shared_ptr<request_call::request>> queue_request::request_map;
