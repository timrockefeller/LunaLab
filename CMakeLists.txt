cmake_minimum_required(VERSION 3.11)

set(PROJECT_NAME "LunaLab")
set(PROJECT_VERSION 0.1.0)

project(${PROJECT_NAME} VERSION ${PROJECT_VERSION} LANGUAGES C CXX)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
include(IKInit)

IK_AddPackage(IKit 0.0.4)
IK_AddPackage(IKMvs 0.0.2)

IK_InitProject(${PROJECT_NAME})

message(STATUS "[Project] ${PROJECT_NAME} ${PROJECT_VERSION}")

include_directories (
    ${PROJECT_SOURCE_DIR}/include
)
link_directories (
    ${PROJECT_SOURCE_DIR}/lib
)

IK_AddSubDirsRec(include)
IK_AddSubDirsRec(src)
