cmake_minimum_required(VERSION 3.6)

#include(GoogleTest)
#add_executable(PrArrQueueTest pr_arr_queue_unittest.cpp)

project(fast-priority-queue)
add_executable(${PROJECT_NAME} "main.cpp")

file(GLOB SOURCES *.h)
