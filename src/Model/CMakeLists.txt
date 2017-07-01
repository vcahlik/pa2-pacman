add_subdirectory(GameObjects)

set(SOURCES
        ${SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/Game.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/GameMap.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/GameTimer.cpp
        PARENT_SCOPE
        )

set(HEADERS
        ${HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/Game.h
        ${CMAKE_CURRENT_SOURCE_DIR}/GameMap.h
        ${CMAKE_CURRENT_SOURCE_DIR}/GameTimer.h
        PARENT_SCOPE
        )
