# 添加第三方依赖包
include(FetchContent)
# FetchContent_MakeAvailable was not added until CMake 3.14
if(${CMAKE_VERSION} VERSION_LESS 3.14)
    include(add_FetchContent_MakeAvailable.cmake)
endif()
message(STATUS "importing IKit")
set(IKIT_GIT_TAG  v0.0.1)  # 指定版本
set(IKIT_GIT_URL  https://github.com/timrockefeller/IKit.git)  # 指定git仓库地址

FetchContent_Declare(
  IKit
  GIT_REPOSITORY    ${IKIT_GIT_URL}
  GIT_TAG           ${IKIT_GIT_TAG}
)

FetchContent_MakeAvailable(IKit)
