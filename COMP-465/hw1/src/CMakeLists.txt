cmake_minimum_required(VERSION 3.0)
project(hello_triangle)

add_executable(hello_triangle main.cpp)

link_libraries(libdl.so)
add_library(glad ${PROJECT_SOURCE_DIR}/glad.c)

find_package(glfw3 3.3 REQUIRED)
target_link_libraries(hello_triangle glad glfw)
