cmake_minimum_required(VERSION 3.7)

project(bpi_ledcontrol VERSION 0.1)

add_subdirectory(wiringPi)

add_library(bpi_ledcontrol ledcontrol.cpp ledcontrol.h binary.h digit.h)
target_link_libraries(bpi_ledcontrol wiringPi)

set(CMAKE_CXX_STANDARD 17)
