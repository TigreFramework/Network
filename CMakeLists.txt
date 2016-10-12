cmake_minimum_required(VERSION 3.4)
project(Network)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(LIB_NETWORK Socket.cpp Socket.h)
set(TEST_NETWORK main.cpp Socket.cpp Socket.h)

add_executable(NetworkTeste ${TEST_NETWORK})
add_library(Network ${LIB_NETWORK})