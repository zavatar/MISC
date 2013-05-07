include_directories(${PROJECT_SOURCE_DIR})

function(CreateTest NAME)
	set(TEST_NAME test-${NAME})
	add_executable(${TEST_NAME} ${NAME}.cpp)
	add_test( 
	    NAME ${TEST_NAME}
	    COMMAND $<TARGET_FILE:${TEST_NAME}>)
endfunction()

file(GLOB SAMPLE_LIST *.cpp)
foreach(Src ${SAMPLE_LIST})
	string(REPLACE "/" ";" srcBlock ${Src})
	list(GET srcBlock -1 cppName)
	string(REPLACE ".cpp" "" Name ${cppName})
	message(STATUS "Find Test: ${Name}")
	CreateTest(${Name})
endforeach()