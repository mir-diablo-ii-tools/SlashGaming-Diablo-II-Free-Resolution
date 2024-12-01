target_sources(${PROJECT_NAME}
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/cfg_indent_width.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/cfg_ingame_resolution.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/cfg_ingame_resolutions.c"
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/cfg_indent_width.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/cfg_ingame_resolution.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/cfg_ingame_resolutions.h")

add_subdirectory("metadata")
