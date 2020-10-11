## For main extry file project
set(MODE "LIB")
set(TARGET_NAME "LunaFramework")
IK_GlobGroupSrcs(RST STR_TARGET_SOURCES PATHS
    ${CMAKE_CURRENT_SOURCE_DIR}
    "${PROJECT_SOURCE_DIR}/include/Editor"
    "${PROJECT_SOURCE_DIR}/include/Editor/Scene"
    "${PROJECT_SOURCE_DIR}/include/Editor/UI"
)
IK_UnityArgs(STR_TARGET_LIBS
    # libs
    glfw3
    glad
    imgui
    opengl32
    LunaUtils
)
IK_SetupProject(${MODE} ${TARGET_NAME} ${STR_TARGET_SOURCES} ${STR_TARGET_LIBS})
