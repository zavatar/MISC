option(TEST_ENABLE_CXX_11 "Enable C++ 11" OFF)
if(TEST_ENABLE_CXX_11)
	if(CMAKE_COMPILER_IS_GNUCXX)
		add_definitions(-std=c++11)
	endif()
elseif(NOT TEST_ENABLE_CXX_11)
	if(CMAKE_COMPILER_IS_GNUCXX)
		add_definitions(-std=c++98)
	endif()
endif()

include_directories("../")
include_directories("./gtest")

function(CreateTest NAME)
	set(SAMPLE_NAME test-${NAME})
	add_executable(${SAMPLE_NAME} ${NAME}.cpp)

	add_test( 
	    NAME ${SAMPLE_NAME}
	    COMMAND $<TARGET_FILE:${SAMPLE_NAME}> )
endfunction()

CreateTest(interval_tree)