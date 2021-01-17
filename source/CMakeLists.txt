cmake_minimum_required(VERSION 3.7)

project(bpi_ledcontrol VERSION 0.1)
set(CMAKE_CXX_STANDARD 14)

# use interface library for including wiringBP
add_subdirectory(wiringPi)

# add static library
set (HEADERS
	bpi_ledcontrol/max7219.h
	bpi_ledcontrol/binary.h
	bpi_ledcontrol/digit.h
)
add_library(bpi_ledcontrol STATIC max7219.cpp ${HEADERS})
target_link_libraries(bpi_ledcontrol PUBLIC wiringPi)
target_include_directories(bpi_ledcontrol PUBLIC ${CMAKE_SOURCE_DIR})

# add test executable
add_executable(bpi_ledcontrol_test test/main.cpp)
target_link_libraries(bpi_ledcontrol_test bpi_ledcontrol)

# install
SET(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})
install(
	TARGETS bpi_ledcontrol bpi_ledcontrol_test
	RUNTIME DESTINATION /usr/local/bin
	ARCHIVE DESTINATION /usr/local/lib
)
install(FILES
	${HEADERS} DESTINATION /usr/local/include/bpi_ledcontrol
)
