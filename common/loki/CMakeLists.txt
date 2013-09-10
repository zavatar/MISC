project(loki_builder)
include(ExternalProject)

message(STATUS "loki path: ${CMAKE_CURRENT_BINARY_DIR}")

if(CMAKE_COMPILER_IS_GNUCXX)
	set (Loki_BUILD_COMMAND make build-static)
  set (Loki_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/src/loki)
  set (Loki_PATCH "")
elseif(MSVC)
  set (Loki_BUILD_COMMAND make.msvc.bat)
  set (Loki_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/src/loki/src)
  set (Loki_PATCH svn revert ${Loki_BINARY_DIR}/SmallObj.cpp
  COMMAND patch ${Loki_BINARY_DIR}/SmallObj.cpp -i ${CMAKE_CURRENT_SOURCE_DIR}/SmallObj.cpp.patch)
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