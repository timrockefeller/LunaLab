IK_AddTarget(
    MODE STATIC
    INC "${PROJECT_SOURCE_DIR}/include"
    SRC
        "${CMAKE_CURRENT_SOURCE_DIR}/UI"
        "${CMAKE_CURRENT_SOURCE_DIR}/Scene"
    LIB 
        KTKR::IKit_core
        KTKR::LunaLab_Basic
        KTKR::LunaLab_IKMath
        KTKR::LunaLab_lib_glad
        KTKR::LunaLab_lib_imgui
        glfw3
        opengl32
)