cmake_minimum_required(VERSION 3.0)
set (CMAKE_CXX_STANDARD 17)
project(viewer)

file(GLOB HEADERS ${PROJECT_SOURCE_DIR}/../include/stb_image.h ${PROJECT_SOURCE_DIR}/../include/*.hpp)
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/*.cpp)

add_executable(viewer ${SOURCES} ${HEADERS})

link_libraries(libdl.so)
add_library(glad ${PROJECT_SOURCE_DIR}/glad.c)

find_package(glfw3 3.3 REQUIRED)
find_package(glm REQUIRED)
find_package(assimp REQUIRED)
target_link_libraries(viewer glad glfw glm assimp)
