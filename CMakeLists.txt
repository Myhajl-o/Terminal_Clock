cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_COMPILER "g++")

project(Clock)
set(cmake_example_2_VERSION "1.0.0.0")

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES main.cpp output.cpp math.cpp Second-hand.cpp)
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	list(APPEND SOURCES linux/input.cpp)
elseif(WIN32)
	list(APPEND SOURCES win/input.cpp)
endif()
list(TRANSFORM SOURCES PREPEND "source/")

add_executable(clock ${SOURCES})

target_include_directories(clock PRIVATE include/)
target_compile_options(clock PRIVATE -Wall -Wextra -Werror -O1)
