target_sources(${PROJECT_NAME}
    PRIVATE
        "patch.cpp"
        "patch.hpp"

        "patch_1_07.cpp"
        "patch_1_07.hpp"
        "patch_1_07_shim_d2client_set_tile_culling_bound.asm"
        "patch_1_07_shim.h"

        "patch_1_11.cpp"
        "patch_1_11.hpp"
        "patch_1_11_shim_d2client_set_tile_culling_bound.asm"
        "patch_1_11_shim.h"

        "replacement.cpp"
        "replacement.hpp"
)
