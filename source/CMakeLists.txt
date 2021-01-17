cmake_minimum_required(VERSION 3.7)

project(max7219 VERSION 0.1)
set(CMAKE_CXX_STANDARD 14)

# use interface library for including wiringBP
add_subdirectory(wiringPi)

# add static library
set (HEADERS
	max7219/max7219.h
	max7219/binary.h
	max7219/digit.h
)
add_library(max7219 STATIC max7219.cpp ${HEADERS})
target_link_libraries(max7219 PUBLIC wiringPi)
target_include_directories(max7219 PUBLIC ${CMAKE_SOURCE_DIR})

# add test executable
add_executable(max7219_test test/main.cpp)
target_link_libraries(max7219_test max7219)

# install
SET(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})
install(
	TARGETS max7219 max7219_test
	RUNTIME DESTINATION /usr/local/bin
	ARCHIVE DESTINATION /usr/local/lib
)
install(FILES
	${HEADERS} DESTINATION /usr/local/include/max7219
)
