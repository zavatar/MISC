include_directories(${PROJECT_SOURCE_DIR})

function(CreateTest NAME)
	set(TEST_NAME test-${NAME})
	add_executable(${TEST_NAME} ${NAME}.cpp)
	add_test( 
	    NAME ${TEST_NAME}
	    COMMAND $<TARGET_FILE:${TEST_NAME}>)
endfunction()

CreateTest(interval_tree)