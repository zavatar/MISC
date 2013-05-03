option(TEST_ENABLE_CXX_11 "Enable C++ 11" OFF)
if(CMAKE_COMPILER_IS_GNUCXX)
	if(TEST_ENABLE_CXX_11)
		add_definitions(-std=c++11)
	endif()
elseif(MSVC)
#vc 2012 fix for vararg templates
    set(MSVC_COMPILER_DEFS "-D_VARIADIC_MAX=10")
	add_definitions(${MSVC_COMPILER_DEFS})
endif()

add_subdirectory(gtest)
include_directories(${GTEST_INCLUDE_DIRS})

set(PROJECT_TEST_NAME ${PROJECT_NAME}_test)

file(GLOB TEST_SOURCE *.cpp)

add_executable(${PROJECT_TEST_NAME} ${TEST_SOURCE})
add_dependencies(${PROJECT_TEST_NAME} googletest)

if(CMAKE_COMPILER_IS_GNUCXX)
	target_link_libraries(${PROJECT_TEST_NAME} pthread)
	target_link_libraries(${PROJECT_TEST_NAME}
		${GTEST_LIBS_DIR}/libgtest.a
		${GTEST_LIBS_DIR}/libgtest_main.a
	)
else()
	target_link_libraries(${PROJECT_TEST_NAME}
	   debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
	   optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
	)
	target_link_libraries(${PROJECT_TEST_NAME}
	   debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
	   optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
	)
endif()

add_test(${PROJECT_TEST_NAME} ${PROJECT_TEST_NAME})