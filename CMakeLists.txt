cmake_minimum_required(VERSION 3.16)

project(Terminal_Clock LANGUAGES C CXX)
set(cmake_example_2_VERSION "1.0.0.0")

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

include_directories(include/)

set(SOURCES main.cpp background.cpp watch_face.cpp Simple_string.cpp Settings_clock.cpp Second-hand.cpp)
list(TRANSFORM SOURCES PREPEND "source/")

set(INPUT)
set(OUTPUT libraries/output.c)
set(MATH libraries/math.cpp)
set(PARSING libraries/parsing.c)


if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	list(APPEND INPUT libraries/linux/input.cpp)
elseif(WIN32)
	list(APPEND INPUT libraries/win/input.cpp)
endif()


add_library(_input_lib SHARED ${INPUT})
add_library(_output_lib SHARED ${OUTPUT})
add_library(_math_lib SHARED ${MATH})
add_library(_parsing_lib SHARED ${PARSING})

target_compile_definitions(_parsing_lib PRIVATE CONF_PATH="${CMAKE_SOURCE_DIR}/configuration/clock.conf")

add_executable(clock ${SOURCES})


target_compile_options(clock PRIVATE -fno-exceptions -fno-rtti -Wall -Wextra -Werror -O2)
target_compile_options(_input_lib PRIVATE -fno-exceptions -fno-rtti -Wall -Wextra -Werror -O2)
target_compile_options(_math_lib PRIVATE -fno-exceptions -fno-rtti -Wall -Wextra -Werror -O2)
set_target_properties(clock _input_lib _math_lib PROPERTIES CXX_STANDARD 98 CXX_STANDARD_REQUIRED ON)

target_compile_options(_output_lib PRIVATE -Wall -Wextra -Werror -O2)
target_compile_options(_parsing_lib PRIVATE -Wall -Wextra -Werror -O2)
set_target_properties(_output_lib _parsing_lib PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED ON C_EXTENSIONS ON)


target_link_libraries(clock PRIVATE _input_lib _output_lib _math_lib _parsing_lib)


