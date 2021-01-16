cmake_minimum_required(VERSION 3.7)

project(wiringPi)

find_path(INCLUDE_DIR NAMES wiringPi.h PATHS /usr/local/include REQUIRED NO_DEFAULT_PATH)
find_library(LIBRARY NAMES libwiringPi.so PATHS /usr/local/lib REQUIRED NO_DEFAULT_PATH)

message (INFO "${INCLUDE_DIR} ${LIBRARY}")

if(INCLUDE_DIR AND LIBRARY)
	add_library(wiringPi INTERFACE)
	target_include_directories(wiringPi INTERFACE ${INCLUDE_DIR})
	target_link_libraries(wiringPi INTERFACE ${LIBRARY})
else()
	message(FATAL "wiringPi not found")
endif()
