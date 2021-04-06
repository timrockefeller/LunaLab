IK_AddTarget(
    MODE EXE
    INC "${PROJECT_SOURCE_DIR}/include"
    LIB 
        KTKR::LunaLab_Basic
        KTKR::LunaLab_Editor
        KTKR::LunaLab_lib_glad
        KTKR::LunaLab_lib_imgui
        glfw3
        opengl32
)