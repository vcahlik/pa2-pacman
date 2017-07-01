add_subdirectory(Ghosts)
add_subdirectory(Navigators)

set(SOURCES
        ${SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/Enemy.cpp
        PARENT_SCOPE
        )

set(HEADERS
        ${HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/Enemy.h
        PARENT_SCOPE
        )
