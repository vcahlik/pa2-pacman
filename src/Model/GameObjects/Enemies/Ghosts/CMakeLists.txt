set(SOURCES
        ${SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/AggressiveGhost.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FreakGhost.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Ghost.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/NormalGhost.cpp
        PARENT_SCOPE
        )

set(HEADERS
        ${HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/AggressiveGhost.h
        ${CMAKE_CURRENT_SOURCE_DIR}/FreakGhost.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Ghost.h
        ${CMAKE_CURRENT_SOURCE_DIR}/NormalGhost.h
        PARENT_SCOPE
        )
