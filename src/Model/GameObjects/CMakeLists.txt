add_subdirectory(Enemies)
add_subdirectory(Items)

set(SOURCES
        ${SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/GameObject.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MovableObject.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Player.cpp
        PARENT_SCOPE
        )

set(HEADERS
        ${HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/GameObject.h
        ${CMAKE_CURRENT_SOURCE_DIR}/MovableObject.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Player.h
        PARENT_SCOPE
        )
