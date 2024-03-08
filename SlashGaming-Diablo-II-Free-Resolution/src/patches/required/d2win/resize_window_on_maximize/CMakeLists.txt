target_sources(${PROJECT_NAME}
    PRIVATE
        "patch.cpp"
        "patch.hpp"

        "patch_1_13c.cpp"
        "patch_1_13c.hpp"
        "patch_1_13c_shim_d2win_resize_window_on_maximize.asm"

        "patch_lod_1_14c.cpp"
        "patch_lod_1_14c.hpp"
        "patch_lod_1_14c_shim_d2win_resize_window_on_maximize.asm"

        "patch_lod_1_14d.cpp"
        "patch_lod_1_14d.hpp"
        "patch_lod_1_14d_shim_d2win_resize_window_on_maximize.asm"

        "replacement.cpp"
        "replacement.hpp"
)
