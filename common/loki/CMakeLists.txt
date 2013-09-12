project(loki_builder)
include(ExternalProject)

message(STATUS "loki path: ${CMAKE_CURRENT_BINARY_DIR}")

set (LOKI_SRC_DIR ${CMAKE_CURRENT_BINARY_DIR}/src/loki)

if(CMAKE_COMPILER_IS_GNUCXX)
	set (Loki_BUILD_COMMAND make build-static)
  set (Loki_BINARY_DIR ${LOKI_SRC_DIR})
  set (Loki_PATCH "")
elseif(MSVC)
  set (Loki_BUILD_COMMAND make.msvc.bat)
  set (Loki_BINARY_DIR ${LOKI_SRC_DIR}/src)
  set (Loki_PATCH svn revert -R ${LOKI_SRC_DIR}
  COMMAND patch ${Loki_BINARY_DIR}/SmallObj.cpp < ${CMAKE_CURRENT_SOURCE_DIR}/SmallObj.cpp.patch)
endif()

ExternalProject_Add(loki
    SVN_REPOSITORY svn://svn.code.sf.net/p/loki-lib/code/trunk
    
    PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
    
    UPDATE_COMMAND ""
    
    PATCH_COMMAND ${Loki_PATCH}
    
    CONFIGURE_COMMAND ""
    
    BINARY_DIR ${Loki_BINARY_DIR}
    
    BUILD_COMMAND ${Loki_BUILD_COMMAND}
    
# Disable install step
    INSTALL_COMMAND ""
)

set(LOKI_INCLUDE_DIRS ${LOKI_SRC_DIR}/include PARENT_SCOPE)
set(LOKI_LIBS_DIR ${LOKI_SRC_DIR}/lib PARENT_SCOPE)