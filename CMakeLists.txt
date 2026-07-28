cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_COMPILER "g++")

project(Terminal_Clock)
set(cmake_example_2_VERSION "1.0.0.0")

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Werror -O1)
include_directories(include/)

set(SOURCES main.cpp background.cpp watch_face.cpp Second-hand.cpp)
#if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
#	list(APPEND SOURCES linux/input.cpp)
#elseif(WIN32)
#	list(APPEND SOURCES win/input.cpp)
#endif()
list(TRANSFORM SOURCES PREPEND "source/")

add_library(_input_lib SHARED libraries/linux/input.cpp)
add_library(_output_lib SHARED libraries/output.cpp)
add_library(_math_lib SHARED libraries/math.cpp)

add_executable(clock ${SOURCES})
#add_executable(clock source/main.cpp libraries/linux/input.cpp libraries/output.cpp libraries/math.cpp source/background.cpp source/watch_face.cpp source/Second-hand.cpp)

target_link_libraries(clock PRIVATE _input_lib _output_lib _math_lib)
