IK_AddTarget(
    TEST
    MODE EXE
    INC "${PROJECT_SOURCE_DIR}/include"
    LIB 
        KTKR::LunaLab_Editor
        KTKR::LunaLab_lib_imgui
        glfw3
        opengl32
)