function(CreateSample NAME)
	set(SAMPLE_NAME sample-${NAME})
	add_executable(${SAMPLE_NAME} ${NAME}.cpp)
	add_test(${SAMPLE_NAME} ${SAMPLE_NAME})
endfunction()

CreateSample(allocator)