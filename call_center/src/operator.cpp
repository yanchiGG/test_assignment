//
// operator.cpp
//

#include <iostream>
#include "../include/operator.hpp"
#include <nlohmann/json.hpp>

operator::operator()
{
  operator_response_time = configuration.config::get_config("operator_response_time");
  id_operator = count_operator;
}

void operator::handle_request(request_call::request& request)
{
    
}

int operator::make_reqister_cdr(request_call::request& request)
{

}

