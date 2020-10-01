function(IK_AddSubDirsRec path)
  message(STATUS "----------")
  file(GLOB_RECURSE children LIST_DIRECTORIES true ${CMAKE_CURRENT_SOURCE_DIR}/${path}/*)
  set(dirs "")
  list(APPEND children "${CMAKE_CURRENT_SOURCE_DIR}/${path}")
  foreach(item ${children})
    if(IS_DIRECTORY ${item} AND EXISTS "${item}/CMakeLists.txt")
      list(APPEND dirs ${item})
    endif()
  endforeach()
  foreach(dir ${dirs})
    add_subdirectory(${dir})
  endforeach()
endfunction()

### IK_UnityArgs
## (tarLIST STR1 STR2 ...)
## -> tarLIST = "STR1 STR2 ..."
function(IK_UnityArgs)
    set(ARGLIST "")
    set(IK_INDEX 1)
    if(${ARGC} LESS 2)
        set(ARGLIST " ")
    else()
        while(IK_INDEX LESS ${ARGC})
            set(ARGLIST "${ARGLIST} ${ARGV${IK_INDEX}}")
            math(EXPR IK_INDEX "${IK_INDEX} + 1")  
        endwhile()
    endif()
    set(${ARGV0} ${ARGLIST} PARENT_SCOPE)
endfunction(IK_UnityArgs)

function(IK_GlobGroupSrcs)
	cmake_parse_arguments("ARG" "" "RST" "PATHS" ${ARGN})
	set(SOURCES "")
	foreach(path ${ARG_PATHS})
		file(GLOB_RECURSE pathSources
			"${path}/*.h"
			"${path}/*.hpp"
			"${path}/*.inl"
			"${path}/*.c"
			"${path}/*.cc"
			"${path}/*.cpp"
			"${path}/*.cxx"
		)
		list(APPEND SOURCES ${pathSources})
    endforeach()
    IK_UnityArgs(SOURCES ${SOURCES})
	set(${ARG_RST} ${SOURCES} PARENT_SCOPE)
endfunction()

### Setup Target
##  TODO setup target with less options, seperate by extensions
## 

function(IK_SetupTarget)

endfunction()
