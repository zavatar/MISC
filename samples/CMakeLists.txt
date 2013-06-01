function(CreateSample NAME)
	set(SAMPLE_NAME sample-${NAME})
	add_executable(${SAMPLE_NAME} ${NAME}.cpp)
	add_test( 
	    NAME ${SAMPLE_NAME}
	    COMMAND $<TARGET_FILE:${SAMPLE_NAME}>)
	if(NAME STREQUAL "virtual_inheritance" AND MSVC)
		set_target_properties(${SAMPLE_NAME} PROPERTIES COMPILE_FLAGS /d1reportSingleClassLayoutDiamondSub)
	elseif(NAME STREQUAL "allocator" AND STLPort)
		set_target_properties(${SAMPLE_NAME} PROPERTIES INCLUDE_DIRECTORIES 
		${PROJECT_SOURCE_DIR}/common/stlport/inc)
	elseif(NAME STREQUAL "google_test")
		set_target_properties(${SAMPLE_NAME} PROPERTIES COMPILE_FLAGS ${COMPILER_DEFS})
		add_dependencies(${SAMPLE_NAME} googletest)
		set_target_properties(${SAMPLE_NAME} PROPERTIES INCLUDE_DIRECTORIES 
		${GTEST_INCLUDE_DIRS})
		if(CMAKE_COMPILER_IS_GNUCXX)
			target_link_libraries(${SAMPLE_NAME} pthread)
			target_link_libraries(${SAMPLE_NAME}
				${GTEST_LIBS_DIR}/libgtest.a
				${GTEST_LIBS_DIR}/libgtest_main.a)
		else()
			target_link_libraries(${SAMPLE_NAME}
				debug ${GTEST_LIBS_DIR}/DebugLibs/gtest.lib
				optimized ${GTEST_LIBS_DIR}/ReleaseLibs/gtest.lib)
		endif()
	endif()
endfunction()

################################
# Add STLPort

if(MSVC)
	option(STLPort "Using STLPort" OFF)
	if (STLPort)
		link_directories(${PROJECT_SOURCE_DIR}/common/stlport/lib)
	endif()
endif()

file(GLOB SAMPLE_LIST *.cpp)
foreach(Src ${SAMPLE_LIST})
	string(REPLACE "/" ";" srcBlock ${Src})
	list(GET srcBlock -1 cppName)
	string(REPLACE ".cpp" "" Name ${cppName})
	message(STATUS "Find Sample: ${Name}")
	CreateSample(${Name})
endforeach()

include_directories(${PROJECT_SOURCE_DIR})