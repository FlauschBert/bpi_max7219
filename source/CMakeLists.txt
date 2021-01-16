cmake_minimum_required(VERSION 3.7)

project(bpi_ledcontrol VERSION 0.1)

add_subdirectory(wiringPi)

add_executable(bpi_ledcontrol main.cpp ledcontrol.cpp ledcontrol.h)
target_link_libraries(bpi_ledcontrol wiringPi)

set(CMAKE_CXX_STANDARD 17)
