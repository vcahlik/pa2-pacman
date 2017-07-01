add_subdirectory(Ncurses)

set(SOURCES
        ${SOURCES}
        PARENT_SCOPE
        )

set(HEADERS
        ${HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/GameView.h
        PARENT_SCOPE
        )
