#include "../include/buffer.hpp"


buff::buff()
{
  buf_ready = false;
  buffer_ = "";
}

std::string buff::get_data()
{
  std::unique_lock<std::mutex> lock(mtx);
  cv.wait(lock, [this]{ return buf_ready; });

  std::string data = buffer_;
  buffer_ = "";
  
  buf_ready = false;
  return data;

}

void buff::set_data(std::string data)
{
  std::lock_guard<std::mutex> lock(mtx);
  buffer_ = data;
    
  buf_ready = true;
  cv.notify_one();
}

