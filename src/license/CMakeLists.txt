target_sources(${PROJECT_NAME}
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/license.c"
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/license.h")

target_compile_definitions(${PROJECT_NAME} PRIVATE SGD2FR_DLLEXPORT)
