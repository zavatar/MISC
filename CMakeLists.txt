cmake_minimum_required(VERSION 2.8.8)
set(PROJECT_NAME MISC)
project(${PROJECT_NAME})
enable_testing()

#CMAKE_BUILD_TOOL

if(CMAKE_CURRENT_SOURCE_DIR EQUAL CMAKE_CURRENT_BINARY_DIR)
	message(FATAL_ERROR "Source and binary directories must be different")
endif(CMAKE_CURRENT_SOURCE_DIR EQUAL CMAKE_CURRENT_BINARY_DIR)

if(CMAKE_COMPILER_IS_GNUCXX)
	#add_definitions(-std=c++11)
endif()

################################
# Add common source 



################################
# Add output directory

if(MSVC)
	set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/build/)
else()
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/build/debug )
	else()
		set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/build/release )
	endif()
endif()

################################
# Add subdirectory

add_subdirectory(misc)
add_subdirectory(test)
add_subdirectory(samples)

install(DIRECTORY misc DESTINATION include)