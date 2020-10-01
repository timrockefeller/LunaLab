## For main extry file project
set(MODE "LIB")
set(TARGET_NAME "imgui")
IK_GlobGroupSrcs(RST STR_TARGET_SOURCES PATHS
    ${CMAKE_CURRENT_SOURCE_DIR}
    "${PROJECT_SOURCE_DIR}/include/imgui"
)
IK_UnityArgs(STR_TARGET_LIBS
    # libs
)
IK_SetupProject(${MODE} ${TARGET_NAME} ${STR_TARGET_SOURCES} ${STR_TARGET_LIBS})
