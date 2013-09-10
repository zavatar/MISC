project(gtest_builder)
include(ExternalProject)

if(MSYS)
	set(DisablePthreads ON)
else()
	set(DisablePthreads OFF)
endif()

message(STATUS "gtest path: ${CMAKE_CURRENT_BINARY_DIR}")

ExternalProject_Add(googletest
    SVN_REPOSITORY http://googletest.googlecode.com/svn/trunk
    CMAKE_ARGS -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=DebugLibs
               -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=ReleaseLibs
               -DCMAKE_CXX_FLAGS=${COMPILER_DEFS}
			   #-DGTEST_USE_OWN_TR1_TUPLE=1
               -Dgtest_force_shared_crt=ON
			   # MinGW doesn't support -pthread
               -Dgtest_disable_pthreads=${DisablePthreads}
    PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
# Disable install step
    INSTALL_COMMAND ""
)

# Specify include dir
ExternalProject_Get_Property(googletest source_dir)
set(GTEST_INCLUDE_DIRS ${source_dir}/include PARENT_SCOPE)

# Specify MainTest's link libraries
ExternalProject_Get_Property(googletest binary_dir)
set(GTEST_LIBS_DIR ${binary_dir} PARENT_SCOPE)



