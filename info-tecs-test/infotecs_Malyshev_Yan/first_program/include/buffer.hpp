#pragma once

#include <string>
#include <mutex>
#include <condition_variable>

class buff
{
  public:
    buff();
    std::string get_data();
    void set_data(std::string data);

  private:
    std::mutex mtx;
    std::condition_variable cv;
    bool buf_ready;
    std::string buffer_;
};


