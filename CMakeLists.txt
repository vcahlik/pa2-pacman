cmake_minimum_required(VERSION 3.7)
project(pacman)

set(CMAKE_CXX_STANDARD 11)

set(GCC_MANDATORY_FLAGS "-Wall -pedantic -Wno-long-long -O0 -ggdb")
set(GCC_CUSTOM_FLAGS "-g")

find_package(Curses REQUIRED)

set(SOURCE_FILES src/main.cpp src/Model/GameObjects/GameObject.cpp src/Model/GameObjects/GameObject.h src/Model/Game.cpp src/Model/Game.h src/Model/GameMap.cpp src/Model/GameMap.h src/Model/GameObjects/MovableObject.cpp src/Model/GameObjects/MovableObject.h src/Config.h src/View/Ncurses/NcursesUI.cpp src/View/Ncurses/NcursesUI.h src/View/Ncurses/ViewConfig.h src/View/Ncurses/NcursesUtils.h src/View/Ncurses/NcursesGameView.cpp src/View/Ncurses/NcursesGameView.h src/View/Ncurses/NcursesUtils.cpp src/Model/GameObjects/Player.cpp src/Model/GameObjects/Player.h src/View/Ncurses/Color.h src/Controller/GameController.cpp src/Controller/GameController.h src/View/GameView.h src/InputKey.h src/Direction.h src/Utils.cpp src/Utils.h src/View/Ncurses/TextGraphics.h)
add_definitions(${GCC_MANDATORY_FLAGS} ${GCC_CUSTOM_FLAGS})
add_executable(pacman ${SOURCE_FILES})
target_link_libraries(pacman ${CURSES_LIBRARIES})
