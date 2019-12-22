cmake_minimum_required(VERSION 3.0)
project(lego_tetris)

add_executable(lego_tetris src/main.cpp)

target_include_directories(lego_tetris PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(lego_tetris PRIVATE ${PROJECT_SOURCE_DIR}/src)

link_libraries(libdl.so)
add_library(glad src/glad.c)

find_package(glfw3 3.3 REQUIRED)
target_link_libraries(lego_tetris glad glfw)
