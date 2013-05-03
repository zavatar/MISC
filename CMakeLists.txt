cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
set(PROJECT_NAME MISC)
project(${PROJECT_NAME} C CXX)
enable_testing()

#CMAKE_BUILD_TOOL

if(CMAKE_CURRENT_SOURCE_DIR EQUAL CMAKE_CURRENT_BINARY_DIR)
	message(FATAL_ERROR "Source and binary directories must be different")
endif(CMAKE_CURRENT_SOURCE_DIR EQUAL CMAKE_CURRENT_BINARY_DIR)

################################
# Add common source 

include_directories("./")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/common")

################################
# Add subdirectory

add_subdirectory(misc)
add_subdirectory(test)
add_subdirectory(samples)

install(DIRECTORY misc DESTINATION include)