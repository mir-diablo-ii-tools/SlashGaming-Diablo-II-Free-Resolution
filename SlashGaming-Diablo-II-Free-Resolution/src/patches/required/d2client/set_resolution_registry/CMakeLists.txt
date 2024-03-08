target_sources(${PROJECT_NAME}
    PRIVATE
        "patch.cpp"
        "patch.hpp"

        "patch_1_09d.cpp"
        "patch_1_09d.hpp"
        "patch_1_09d_shim_d2client_set_resolution_registry.asm"

        "patch_1_13c.cpp"
        "patch_1_13c.hpp"
        "patch_1_13c_shim_d2client_set_resolution_registry.asm"

        "patch_lod_1_14c.cpp"
        "patch_lod_1_14c.hpp"
        "patch_lod_1_14c_shim_d2client_set_resolution_registry.asm"

        "replacement.cpp"
        "replacement.hpp"
)
