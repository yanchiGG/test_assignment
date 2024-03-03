//
// operator.hpp
//

#pragma once

#include <iostream>
#include "../include/request.hpp"
class operator
{
  private:
    static int count_operator;
    int operator_response_time;
    int id_operator;
  
  public:
    operator(request_call::request& request);

    void handle_request(request_call::request& request);
    
    int make_reqister_cdr(request_call::request& request);

};
