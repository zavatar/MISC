add_definitions(${COMPILER_DEFS})

add_subdirectory(gtest)
# for sample-google_test
set(GTEST_INCLUDE_DIRS ${GTEST_INCLUDE_DIRS} PARENT_SCOPE)
set(GTEST_LIBS_DIR ${GTEST_LIBS_DIR} PARENT_SCOPE)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})

set(TEST_NAME tests)

file(GLOB TEST_SOURCE *.cpp)

add_executable(${TEST_NAME} ${TEST_SOURCE})
add_dependencies(${TEST_NAME} googletest)

if(CMAKE_COMPILER_IS_GNUCXX)
	target_link_libraries(${TEST_NAME} pthread)
	target_link_libraries(${TEST_NAME}
		${GTEST_LIBS_DIR}/libgtest.a
		${GTEST_LIBS_DIR}/libgtest_main.a
	)
else()
	target_link_libraries(${TEST_NAME}
	   debug ${GTEST_LIBS_DIR}/DebugLibs/gtest.lib
	   optimized ${GTEST_LIBS_DIR}/ReleaseLibs/gtest.lib)
	target_link_libraries(${TEST_NAME}
	   debug ${GTEST_LIBS_DIR}/DebugLibs/gtest_main.lib
	   optimized ${GTEST_LIBS_DIR}/ReleaseLibs/gtest_main.lib)
endif()

add_test(NAME ${TEST_NAME}
	    COMMAND $<TARGET_FILE:${TEST_NAME}>)