cmake_minimum_required(VERSION 3.0)
project(pyramid)

add_executable(pyramid main.cpp ../include/Shader.hpp ../include/Camera.hpp ../include/stb_image.h)

link_libraries(libdl.so)
add_library(glad ${PROJECT_SOURCE_DIR}/glad.c)

find_package(glfw3 3.3 REQUIRED)
find_package(glm REQUIRED)
target_link_libraries(pyramid glad glfw glm)
