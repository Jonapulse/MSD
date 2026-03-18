cmake_minimum_required(VERSION 4.1)
project(MallocReplacement)

set(CMAKE_CXX_STANDARD 17)

add_executable(MallocReplacement main.cpp
        MyMemory.cpp
        MyMemory.h
        HashTable.cpp
        HashTable.h)
