target_sources(${PROJECT_NAME}
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/cfg_globals_test.c"
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/cfg_globals_test.h")

add_subdirectory("globals")
add_subdirectory("metadata")
