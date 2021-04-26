IK_AddTarget(
    MODE STATIC
    SRC
        "${CMAKE_CURRENT_SOURCE_DIR}/Obj"
    INC
        "${PROJECT_SOURCE_DIR}/include"
    LIB
        KTKR::IKit_core
        KTKR::LunaLab_Basic
        KTKR::LunaLab_lib_glad
        opengl32
        assimp
)