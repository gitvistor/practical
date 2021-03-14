cmake_minimum_required(VERSION 3.1)

project(Timer)

message(STATUS "PROJECT_SOURCE_DIR is " ${PROJECT_SOURCE_DIR})
message(STATUS "PROJECT_BINARY_DIR is " ${PROJECT_BINARY_DIR})

add_definitions(-g -std=c++11)

# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

set(type 1)

if(${type} EQUAL 1)
    message(STATUS "heap timer")
    include_directories(${PROJECT_SOURCE_DIR}/include/heap)
    aux_source_directory(src/heap TIMER_SRC)
    set(SRC_MAIN ${PROJECT_SOURCE_DIR}/heap_main.cpp)
elseif(${type} EQUAL 2)
    message(STATUS "list timer")
    include_directories(${PROJECT_SOURCE_DIR}/include/list)
    aux_source_directory(src/list TIMER_SRC)
    set(SRC_MAIN ${PROJECT_SOURCE_DIR}/list_main.cpp)
endif()

add_executable(timer ${SRC_MAIN} ${TIMER_SRC})
