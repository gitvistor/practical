cmake_minimum_required(VERSION 3.1)

set(CMAKE_C_COMPILER "/usr/local/gcc-9.3.0/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/local/gcc-9.3.0/bin/g++")

project(logdemo)

message(STATUS "PROJECT_SOURCE_DIR is " ${PROJECT_SOURCE_DIR})
message(STATUS "PROJECT_BINARY_DIR is " ${PROJECT_BINARY_DIR})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_definitions(-DSTATISTICS)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -pthread")

message(STATUS "CMAKE_CXX_FLAGS is " ${CMAKE_CXX_FLAGS})

include_directories(${PROJECT_SOURCE_DIR}/public)
include_directories(${PROJECT_SOURCE_DIR}/logger)
include_directories(${PROJECT_SOURCE_DIR}/logLine)
include_directories(${PROJECT_SOURCE_DIR}/ringBuffer)

aux_source_directory(logger LOGGER_SRC)
aux_source_directory(logLine LogLine_SRC)
aux_source_directory(ringBuffer BUF_SRC)

add_executable(logger main.cpp ${LOGGER_SRC} ${LogLine_SRC} ${BUF_SRC})