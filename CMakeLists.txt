cmake_minimum_required(VERSION 3.6)
project(untitled)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(main main.c file_read.c)
target_link_libraries(main
		"${CMAKE_SOURCE_DIR}/libft.a"
		"-lmlx"
		"-framework OpenGL"
		"-framework AppKit"
		)