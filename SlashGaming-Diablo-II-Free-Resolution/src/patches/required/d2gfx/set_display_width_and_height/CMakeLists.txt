target_sources(${PROJECT_NAME}
    PRIVATE
        "patch.cpp"
        "patch.hpp"

        "patch_1_09d.cpp"
        "patch_1_09d.hpp"
        "patch_1_09d_shim_d2gfx_set_display_width_and_height.asm"

        "patch_1_12a.cpp"
        "patch_1_12a.hpp"
        "patch_1_12a_shim_d2gfx_set_display_width_and_height.asm"

        "patch_1_13c.cpp"
        "patch_1_13c.hpp"
        "patch_1_13c_shim_d2gfx_set_display_width_and_height.asm"

        "replacement.cpp"
        "replacement.hpp"
)
