cmake_minimum_required(VERSION 3.1)

project(Timer)

message(STATUS "PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})
message(STATUS "PROJECT_BINARY_DIR: " ${PROJECT_BINARY_DIR})

add_definitions(-g -std=c++11)

# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

include_directories(${PROJECT_SOURCE_DIR}/include)

aux_source_directory(heap HEAP_SRC)

set(SRC_LIST ${PROJECT_SOURCE_DIR}/timer_main.cpp)

add_executable(timer ${SRC_LIST} ${HEAP_SRC})
