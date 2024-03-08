target_sources(${PROJECT_NAME}
    PRIVATE
        "patch.cpp"
        "patch.hpp"

        "patch_1_13c.cpp"
        "patch_1_13c.hpp"
        "patch_1_13c_shim_d2gfx_is_need_resize_window.asm"

        "patch_1_13d.cpp"
        "patch_1_13d.hpp"

        "replacement.cpp"
        "replacement.hpp"
)
