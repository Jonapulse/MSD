cmake_minimum_required(VERSION 3.5)

project(MyFirstSFMLGame)

find_package(SFML 3.0.1 REQUIRED COMPONENTS System Window Graphics)

add_executable(MyFirstSFMLGame src/main.cpp)

target_link_libraries(MyFirstSFMLGame PRIVATE SFML::System SFML::Window SFML::Graphics)