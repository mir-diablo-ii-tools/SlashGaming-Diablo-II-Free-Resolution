target_sources(${PROJECT_NAME}
    PRIVATE
        "patch.cpp"
        "patch.hpp"

        "patch_1_09.cpp"
        "patch_1_09.hpp"
        "patch_1_09_shim_d2client_set_general_display_width_and_height.asm"

        "replacement.cpp"
        "replacement.hpp"
)
