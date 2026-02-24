cmake_minimum_required(VERSION 3.10.0)
project(MSDscriptGenTests VERSION 0.1.0 LANGUAGES C CXX)

add_executable(MSDscriptGenTests exec.cpp run_msdscript.cpp)

include(CTest)
enable_testing()

