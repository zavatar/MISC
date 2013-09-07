cmake_minimum_required(VERSION 2.8.7)
set(PROJECT_NAME MISC)
project(${PROJECT_NAME})
enable_testing()

#CMAKE_BUILD_TOOL

if(CMAKE_CURRENT_SOURCE_DIR EQUAL CMAKE_CURRENT_BINARY_DIR)
	message(FATAL_ERROR "Source and binary directories must be different")
endif(CMAKE_CURRENT_SOURCE_DIR EQUAL CMAKE_CURRENT_BINARY_DIR)

################################
# Add common source 

find_package(Boost COMPONENTS)
if(NOT Boost_FOUND)
  message(FATAL_ERROR "Boost not found")
endif()

include_directories(${Boost_INCLUDE_DIRS})

if(CMAKE_COMPILER_IS_GNUCXX)
	#set ( CMAKE_VERBOSE_MAKEFILE ON )
	#set ( CMAKE_RULE_MESSAGES OFF )
	add_definitions(-march=native -mfpmath=sse -std=c++11) #-mavx caused Illegal Instruction on AWS
	set(COMPILER_DEFS "-U__STRICT_ANSI__")
elseif(MSVC)
	#add_definitions(/arch:AVX)
#vc 2012 fix for vararg templates
    set(COMPILER_DEFS "-D_VARIADIC_MAX=10")
endif()

################################
# Add output directory

if(MSVC)
	set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/build/)
else()
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/build/debug)
		message(STATUS "Debug")
	else()
		set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/build/release)
		message(STATUS "Release")
	endif()
endif()

################################
# Add subdirectory

add_subdirectory(misc)
add_subdirectory(test)
add_subdirectory(samples)

install(DIRECTORY misc DESTINATION include)
