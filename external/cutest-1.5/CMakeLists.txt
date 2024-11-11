cmake_minimum_required(VERSION 3.24)

# Name of the project, also is the name of the file
project(CuTest)

# Define requirements for C
set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Remove MinGW compiled binary "lib" prefix
if (MINGW)
    set(CMAKE_IMPORT_LIBRARY_PREFIX "")
    set(CMAKE_SHARED_LIBRARY_PREFIX "")
    set(CMAKE_STATIC_LIBRARY_PREFIX "")
endif (MINGW)

# Define DLL target
add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME}
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/CuTest.c"
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/CuTest.h")

target_compile_definitions(${PROJECT_NAME} PRIVATE NOMINMAX)
