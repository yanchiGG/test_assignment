#pragma once
#include <list>
#include <map>
#include <memory>
#include "../include/request.hpp"

struct queue_request 
{
private:
  static std::list<int> request_queue;
  
  static std::map<int, std::shared_ptr<request_call::request> >  request_map;

public:
  static void put_in_queue(int number, const std::shared_ptr<request_call::request> req);

 // static std::shared_ptr<request_call::request> get_of_queue();
  
  static void get_of_queue();
  
  static bool in_queue(int number);
  
  static int first_in_queue();

  static int get_size_queue();

  static void write();

};
