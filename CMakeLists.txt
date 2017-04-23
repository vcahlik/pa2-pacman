cmake_minimum_required(VERSION 3.7)
project(pacman)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp)
add_executable(pacman ${SOURCE_FILES})