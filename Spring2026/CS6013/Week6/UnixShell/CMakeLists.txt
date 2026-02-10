cmake_minimum_required(VERSION 3.10.0)
project(JShell VERSION 0.1.0 LANGUAGES C CXX)

add_executable(JShell jshell.cpp main.cpp shelpers.cpp)

include(CTest)
enable_testing()

