cmake_minimum_required(VERSION 3.10)

project(Clock)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(clock main.cpp background.cpp Second-hand.cpp Minute-hand.cpp)

target_include_directories(clock PRIVATE include/)

target_compile_options(clock PRIVATE -Wall -Wextra -O1)
