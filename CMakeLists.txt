cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_COMPILER "g++")

project(Terminal_Clock)
set(cmake_example_2_VERSION "1.0.0.0")

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Werror -O1)
include_directories(include/)

set(SOURCES main.cpp background.cpp watch_face.cpp Simple_string.cpp Settings_clock.cpp Second-hand.cpp)
list(TRANSFORM SOURCES PREPEND "source/")

set(INPUT)
set(OUTPUT libraries/output.cpp)
set(MATH libraries/math.cpp)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	list(APPEND INPUT libraries/linux/input.cpp)
elseif(WIN32)
	list(APPEND INPUT libraries/win/input.cpp)
endif()


add_library(_input_lib SHARED ${INPUT})
add_library(_output_lib SHARED ${OUTPUT})
add_library(_math_lib SHARED ${MATH})

add_executable(clock ${SOURCES})

target_link_libraries(clock PRIVATE _input_lib _output_lib _math_lib)
