target_sources(${PROJECT_NAME}
    PRIVATE
        "patch.cpp"
        "patch.hpp"

        "patch_1_09d.cpp"
        "patch_1_09d.hpp"
        "patch_1_09d_shim_d2client_draw_interface_bar_background.asm"

        "patch_lod_1_14c.cpp"
        "patch_lod_1_14c.hpp"
        "patch_lod_1_14c_shim_d2client_draw_interface_bar_background.asm"

        "patch_lod_1_14d.cpp"
        "patch_lod_1_14d.hpp"
        "patch_lod_1_14d_shim_d2client_draw_interface_bar_background.asm"

        "replacement.cpp"
        "replacement.hpp"
)
