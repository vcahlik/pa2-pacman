cmake_minimum_required(VERSION 3.7)
project(pacman)

set(CMAKE_CXX_STANDARD 14)

set(CXX_MANDATORY_FLAGS "-Wall -pedantic -Wno-long-long -O0 -ggdb")
set(CXX_CUSTOM_FLAGS "-g")

set(SOURCES "")
set(HEADERS "")

include_directories(${CMAKE_SOURCE_DIR}/src)

add_subdirectory(src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_MANDATORY_FLAGS} ${CXX_CUSTOM_FLAGS}")

add_executable(pacman ${SOURCES} ${HEADERS})

find_package(Curses REQUIRED)
target_link_libraries(pacman ${CURSES_LIBRARIES})
