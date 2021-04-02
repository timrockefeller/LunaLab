IK_AddTarget(
    MODE STATIC
    INC
        "${PROJECT_SOURCE_DIR}/include"
    LIB
        KTKR::LunaLab_Basic
        KTKR::LunaLab_lib_glad
        opengl32
        assimp
)