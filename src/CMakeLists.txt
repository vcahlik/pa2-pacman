add_subdirectory(Model)
add_subdirectory(View)
add_subdirectory(Controller)

set(SOURCES
        ${SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/Coordinates.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Difficulty.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Position.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LevelConfig.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Utils.cpp
        PARENT_SCOPE
        )

set(HEADERS
        ${HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/Coordinates.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Config.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Difficulty.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Direction.h
        ${CMAKE_CURRENT_SOURCE_DIR}/InputKey.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Position.h
        ${CMAKE_CURRENT_SOURCE_DIR}/LevelConfig.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Utils.h
        PARENT_SCOPE
        )
