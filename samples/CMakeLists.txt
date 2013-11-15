function(CreateSample NAME)
	set(SAMPLE_NAME sample-${NAME})
	add_executable(${SAMPLE_NAME} ${NAME}.cpp)
	add_test( 
	    NAME ${SAMPLE_NAME}
	    COMMAND $<TARGET_FILE:${SAMPLE_NAME}>)
  add_dependencies(${SAMPLE_NAME} loki)
	if(NAME STREQUAL "virtual_inheritance" AND MSVC)
		set_target_properties(${SAMPLE_NAME} PROPERTIES COMPILE_FLAGS /d1reportSingleClassLayoutDiamondSub)
	elseif(NAME STREQUAL "google_test")
		set_target_properties(${SAMPLE_NAME} PROPERTIES COMPILE_FLAGS ${COMPILER_DEFS})
		add_dependencies(${SAMPLE_NAME} googletest)
		if(CMAKE_COMPILER_IS_GNUCXX)
			target_link_libraries(${SAMPLE_NAME}
				${GTEST_LIBS_DIR}/libgtest.a
				${GTEST_LIBS_DIR}/libgtest_main.a)
		else()
			target_link_libraries(${SAMPLE_NAME}
				debug ${GTEST_LIBS_DIR}/DebugLibs/gtest.lib
				optimized ${GTEST_LIBS_DIR}/ReleaseLibs/gtest.lib)
		endif()
  elseif(NAME STREQUAL "loki_modern_cplusplus")
    if(CMAKE_COMPILER_IS_GNUCXX)
			target_link_libraries(${SAMPLE_NAME}
				${LOKI_LIBS_DIR}/libloki.a)
		else()
			target_link_libraries(${SAMPLE_NAME}
				debug ${LOKI_LIBS_DIR}/loki.lib
				optimized ${LOKI_LIBS_DIR}/loki.lib)
		endif()
	endif()
	if(CMAKE_COMPILER_IS_GNUCXX)
		target_link_libraries(${SAMPLE_NAME} -lpthread)
		target_link_libraries(${SAMPLE_NAME} -lrt)
	endif()
endfunction()

################################
if(MSVC)
	add_subdirectory(masm)
endif()
################################

file(GLOB SAMPLE_LIST *.cpp)
foreach(Src ${SAMPLE_LIST})
	string(REPLACE "/" ";" srcBlock ${Src})
	list(GET srcBlock -1 cppName)
	string(REPLACE ".cpp" "" Name ${cppName})
	message(STATUS "Find Sample: ${Name}")
	CreateSample(${Name})
endforeach()

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${LOKI_INCLUDE_DIRS})