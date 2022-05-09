cmake_minimum_required(VERSION 3.22)
project(test_data_stream)

set(CMAKE_CXX_STANDARD 14)

add_executable(test_data_stream main.cpp DataStream.cpp DataStream.h ThreadTask.cpp ThreadTask.h)
