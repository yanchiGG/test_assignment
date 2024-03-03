cmake_minimum_required(VERSION 3.5)
project(first_program)

find_package(Boost 1.70 REQUIRED COMPONENTS system thread)
if(Boost_FOUND)
  message(STATUS "Boost found")
else()
  message(FATAL_ERROR "Boost not found")
endif()

set(
  SOURCES 
    src/main.cpp
    src/buffer.cpp
)
set(
  HEADERS
    include/buffer.hpp    
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
