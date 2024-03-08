target_sources(${PROJECT_NAME}
    PRIVATE
        "patch.cpp"
        "patch.hpp"

        "patch_1_13c.cpp"
        "patch_1_13c.hpp"
        "patch_1_13c_shim_d2gfx_is_need_restore_down_window.asm"

        "replacement.cpp"
        "replacement.hpp"
)
