## For main extry file project
set(MODE "LIB")
set(TARGET_NAME "LunaGL")
IK_GlobGroupSrcs(RST STR_TARGET_SOURCES PATHS
    ${CMAKE_CURRENT_SOURCE_DIR}
    "${PROJECT_SOURCE_DIR}/include/Core/OpenGL"
)
IK_UnityArgs(STR_TARGET_LIBS
    # libs
    glad
    opengl32
    LunaUtil
    assimp
)
IK_SetupProject(${MODE} ${TARGET_NAME} ${STR_TARGET_SOURCES} ${STR_TARGET_LIBS})
