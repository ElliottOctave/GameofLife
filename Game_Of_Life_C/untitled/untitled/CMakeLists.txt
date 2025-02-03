cmake_minimum_required(VERSION 3.23)
project(untitled C)

set(CMAKE_C_STANDARD 99)

find_package(SDL2 REQUIRED SDL2)
include_directories(untitled ${SDL2_INCLUDE_DIRS})

add_executable(untitled main.c Procedures.c Procedures.h GUI.c GUI.h)
target_link_libraries(untitled ${SDL2_LIBRARIES})
