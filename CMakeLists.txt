cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(MISC)
enable_testing()

#CMAKE_BUILD_TOOL

if(CMAKE_CURRENT_SOURCE_DIR EQUAL CMAKE_CURRENT_BINARY_DIR)
	message(FATAL_ERROR "Source and binary directories must be different")
endif(CMAKE_CURRENT_SOURCE_DIR EQUAL CMAKE_CURRENT_BINARY_DIR)

################################
# Add common source 

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/common")

################################
# Add output directory

if(MSVC)
	set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/build/)
else(MSVC)
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/build/debug )
	else(CMAKE_BUILD_TYPE STREQUAL "Debug")
		set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/build/release )
	endif(CMAKE_BUILD_TYPE STREQUAL "Debug")
endif(MSVC)

################################
# Add subdirectory

add_subdirectory(misc)
add_subdirectory(test)
add_subdirectory(samples)

install(DIRECTORY misc DESTINATION include)