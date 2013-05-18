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