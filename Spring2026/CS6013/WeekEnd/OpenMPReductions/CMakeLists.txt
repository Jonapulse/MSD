cmake_minimum_required(VERSION 3.16)
project(parallel_sum)

set(CMAKE_CXX_STANDARD 17)

# Point to Homebrew's libomp (adjust path if on Intel Mac)
execute_process(COMMAND brew --prefix libomp
        OUTPUT_VARIABLE LIBOMP_PREFIX
        OUTPUT_STRIP_TRAILING_WHITESPACE)

add_executable(parallel_sum parallel_sum.cpp)

target_compile_options(parallel_sum PRIVATE -Xpreprocessor -fopenmp)
target_include_directories(parallel_sum PRIVATE ${LIBOMP_PREFIX}/include)
target_link_libraries(parallel_sum PRIVATE ${LIBOMP_PREFIX}/lib/libomp.dylib)