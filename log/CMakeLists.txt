cmake_minimum_required(VERSION 3.1)

set(CMAKE_C_COMPILER "/usr/local/gcc-9.3.0/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/local/gcc-9.3.0/bin/g++")

project(logdemo)

message(STATUS "PROJECT_SOURCE_DIR is " ${PROJECT_SOURCE_DIR})
message(STATUS "PROJECT_BINARY_DIR is " ${PROJECT_BINARY_DIR})
message(STATUS "EXECUTABLE_OUTPUT_PATH is " ${PROJECT_SOURCE_DIR}/bin)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -pthread")

message(STATUS "CMAKE_CXX_FLAGS is " ${CMAKE_CXX_FLAGS})

add_executable(logger main.cpp log.cpp)