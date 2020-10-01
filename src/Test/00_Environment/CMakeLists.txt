## For main extry file project
set(MODE "EXE")
set(TARGET_NAME "example")
IK_UnityArgs(STR_TARGET_SOURCES
    # sources, headfiles
    "main.cpp"
)
IK_UnityArgs(STR_TARGET_LIBS
    # libs
    glfw3
    glad
    imgui
    LunaFramework
)
IK_SetupProject(${MODE} ${TARGET_NAME} ${STR_TARGET_SOURCES} ${STR_TARGET_LIBS})
