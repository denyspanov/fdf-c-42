cmake_minimum_required(VERSION 3.6)
project(fdf_c_42)

set(CMAKE_CXX_STANDARD 11)

add_executable(fdf_c_42 main.c file_read.c)

target_link_libraries(fdf_c_42 ${CMAKE_SOURCE_DIR}/libft.a "-lmlx")