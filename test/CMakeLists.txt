if(CMAKE_COMPILER_IS_GNUCXX)
	set(COMPILER_DEFS "-U__STRICT_ANSI__")
elseif(MSVC)
#vc 2012 fix for vararg templates
    set(COMPILER_DEFS "-D_VARIADIC_MAX=10")
endif()
add_definitions(${COMPILER_DEFS})

add_subdirectory(gtest)
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${GTEST_INCLUDE_DIRS})

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
	   debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
	   optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
	)
	target_link_libraries(${TEST_NAME}
	   debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
	   optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
	)
endif()

add_test(${TEST_NAME} ${TEST_NAME})