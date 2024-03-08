target_sources(${PROJECT_NAME}
    PRIVATE
        "patch.cpp"
        "patch.hpp"

        "patch_1_09d.cpp"
        "patch_1_09d.hpp"
        "patch_1_09d_shim_d2gdi_set_bit_block_width_and_height.asm"

        "patch_1_13c.cpp"
        "patch_1_13c.hpp"
        "patch_1_13c_shim_d2gdi_set_bit_block_width_and_height.asm"

        "patch_lod_1_14a.cpp"
        "patch_lod_1_14a.hpp"
        "patch_lod_1_14a_shim_d2gdi_set_bit_block_width_and_height.asm"

        "replacement.cpp"
        "replacement.hpp"
)
