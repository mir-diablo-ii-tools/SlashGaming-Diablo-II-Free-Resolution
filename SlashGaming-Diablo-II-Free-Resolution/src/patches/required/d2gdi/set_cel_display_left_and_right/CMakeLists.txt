target_sources(${PROJECT_NAME}
    PRIVATE
        "patch.cpp"
        "patch.hpp"

        "patch_1_09d.cpp"
        "patch_1_09d.hpp"
        "patch_1_09d_shim_d2gdi_set_cel_display_left_and_right.asm"

        "patch_1_13c.cpp"
        "patch_1_13c.hpp"
        "patch_1_13c_shim_d2gdi_set_cel_display_left_and_right.asm"

        "replacement.cpp"
        "replacement.hpp"
)
