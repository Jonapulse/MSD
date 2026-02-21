cmake_minimum_required(VERSION 3.10.0)
project(MSDscript VERSION 0.1.0 LANGUAGES C CXX)

add_executable(MSDscript cmdline.cpp expr.cpp main.cpp parse.cpp)

include(CTest)
enable_testing()

