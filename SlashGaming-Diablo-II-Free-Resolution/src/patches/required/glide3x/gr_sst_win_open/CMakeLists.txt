target_sources(${PROJECT_NAME}
    PRIVATE
        "patch.cpp"
        "patch.hpp"

        "patch_nglide_3_10_0_658.cpp"
        "patch_nglide_3_10_0_658.hpp"
        "patch_nglide_3_10_0_658_shim_glide3x_gr_sst_win_open.asm"

        "patch_sven_1_4_4_21.cpp"
        "patch_sven_1_4_4_21.hpp"
        "patch_sven_1_4_4_21_shim_glide3x_gr_sst_win_open.asm"

        "patch_sven_1_4_8_3.cpp"
        "patch_sven_1_4_8_3.hpp"
        "patch_sven_1_4_8_3_shim_glide3x_gr_sst_win_open.asm"

        "replacement.cpp"
        "replacement.hpp"
)
