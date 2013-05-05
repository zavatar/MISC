function(CreateSample NAME)
	set(SAMPLE_NAME sample-${NAME})
	add_executable(${SAMPLE_NAME} ${NAME}.cpp)
	add_test(${SAMPLE_NAME} ${SAMPLE_NAME})
endfunction()

################################
# Add STLPort

if(MSVC)
	option(STLPort "Using STLPort" OFF)
	if(STLPort)
		include_directories(${PROJECT_SOURCE_DIR}/common/stlport/inc)
		link_directories(${PROJECT_SOURCE_DIR}/common/stlport/lib)
	endif()
endif()

include_directories(${PROJECT_SOURCE_DIR})

CreateSample(allocator)