target_sources(${PROJECT_NAME}
    PRIVATE
        "required_patches.cc"
        "required_patches.hpp"
)

add_subdirectory(d2client)
add_subdirectory(d2ddraw)
add_subdirectory(d2direct3d)
add_subdirectory(d2gdi)
add_subdirectory(d2gfx)
add_subdirectory(d2glide)
add_subdirectory(d2win)
add_subdirectory(glide3x)
