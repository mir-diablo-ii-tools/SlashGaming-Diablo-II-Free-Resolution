target_sources(${PROJECT_NAME}
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/cfg_globals.c"
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/cfg_globals.h")

add_subdirectory("globals")
