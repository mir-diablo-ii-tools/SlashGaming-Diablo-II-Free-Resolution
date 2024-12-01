target_sources(${PROJECT_NAME}
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/cfg_indent_width_test.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/cfg_ingame_resolution_test.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/cfg_ingame_resolutions_test.c"
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/cfg_indent_width_test.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/cfg_ingame_resolution_test.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/cfg_ingame_resolutions_test.h")

add_subdirectory("metadata")
