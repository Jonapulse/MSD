cmake_minimum_required(VERSION 4.1)
project(ThreadSafeQueue)

set(CMAKE_CXX_STANDARD 17)

add_executable(ThreadSafeQueue
  #      SerialQueueTests.cpp
  #      SerialQueue.hpp
        ConcurrentQueue.hpp
        ConcurrentQueueTest.cpp
)
