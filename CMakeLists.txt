cmake_minimum_required(VERSION 3.7)
project(pacman)

set(CMAKE_CXX_STANDARD 11)

set(GCC_MANDATORY_FLAGS "-Wall -pedantic -Wno-long-long -O0 -ggdb")
set(GCC_CUSTOM_FLAGS "")

find_package(Curses REQUIRED)

set(SOURCE_FILES src/main.cpp src/Model/GameObjects/GameObject.cpp src/Model/GameObjects/GameObject.h src/Model/Game.cpp src/Model/Game.h src/Model/GameMap.cpp src/Model/GameMap.h src/Model/GameObjects/MovableObject.cpp src/Model/GameObjects/MovableObject.h src/Model/Config.cpp src/Model/Config.h src/Views/Ncurses/NcursesView.cpp src/Views/Ncurses/NcursesView.h)
add_definitions(${GCC_MANDATORY_FLAGS} ${GCC_CUSTOM_FLAGS})
add_executable(pacman ${SOURCE_FILES})
target_link_libraries(pacman ${CURSES_LIBRARIES})