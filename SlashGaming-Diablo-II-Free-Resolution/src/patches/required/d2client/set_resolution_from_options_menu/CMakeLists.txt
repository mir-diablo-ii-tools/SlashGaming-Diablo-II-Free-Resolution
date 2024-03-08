target_sources(${PROJECT_NAME}
    PRIVATE
        "patch.cpp"
        "patch.hpp"

        "patch_1_09.cpp"
        "patch_1_09.hpp"
        "patch_1_09_shim_d2client_set_resolution_from_options_menu.asm"

        "patch_1_13c.cpp"
        "patch_1_13c.hpp"
        "patch_1_13c_shim_d2client_set_resolution_from_options_menu.asm"

        "replacement.cpp"
        "replacement.hpp"
)
