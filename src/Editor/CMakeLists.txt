## For main extry file project
set(MODE "LIB")
set(TARGET_NAME "LunaFramework")
IK_GlobGroupSrcs(RST STR_TARGET_SOURCES PATHS
    ${CMAKE_CURRENT_SOURCE_DIR}
    "${PROJECT_SOURCE_DIR}/include/Editor"
)
IK_UnityArgs(STR_TARGET_LIBS
    # libs
    glfw3.lib
    glad
    opengl32.lib
)
IK_SetupProject(${MODE} ${TARGET_NAME} ${STR_TARGET_SOURCES} ${STR_TARGET_LIBS})
