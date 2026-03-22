cmake_minimum_required(VERSION 3.14)
project(MallocReplacement)

set(CMAKE_CXX_STANDARD 17)

# Download and configure GoogleTest
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

add_library(hashtable_lib
        src/HashTable.cpp
        src/HashTable.h
)

add_library(mymalloc_lib
    src/MyMalloc.cpp
    src/MyMalloc.h
)

add_executable(MallocReplacement src/main.cpp)
target_link_libraries(MallocReplacement hashtable_lib mymalloc_lib)

add_executable(HashTableTests tests/HashTableTest.cpp)
target_link_libraries(HashTableTests
        hashtable_lib
        GTest::gtest_main
)

add_executable(MyMallocTests tests/MyMallocTest.cpp)
target_link_libraries(MyMallocTests
    mymalloc_lib
    hashtable_lib
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(HashTableTests)