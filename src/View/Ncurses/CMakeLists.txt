set(SOURCES
        ${SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/NcursesGameView.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/NcursesUI.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/NcursesUtils.cpp
        PARENT_SCOPE
        )

set(HEADERS
        ${HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/Color.h
        ${CMAKE_CURRENT_SOURCE_DIR}/NcursesGameView.h
        ${CMAKE_CURRENT_SOURCE_DIR}/NcursesUI.h
        ${CMAKE_CURRENT_SOURCE_DIR}/TextGraphics.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ViewConfig.h
        PARENT_SCOPE
        )
