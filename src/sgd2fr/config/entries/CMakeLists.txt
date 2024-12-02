target_sources(${PROJECT_NAME}
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/cfg_custom_mpq_file_path.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/cfg_indent_width.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/cfg_ingame_resolution.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/cfg_ingame_resolutions.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/cfg_main_menu_resolution.c"
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/cfg_custom_mpq_file_path.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/cfg_indent_width.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/cfg_ingame_resolution.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/cfg_ingame_resolutions.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/cfg_main_menu_resolution.h")

add_subdirectory("metadata")
