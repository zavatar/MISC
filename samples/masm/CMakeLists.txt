set(SAMPLE_NAME sample-masm)
set_source_files_properties(code.c PROPERTIES COMPILE_FLAGS 
"-Fa${CMAKE_CURRENT_SOURCE_DIR}/code.asm -FA")
set_property(SOURCE main.c PROPERTY COMPILE_FLAGS 
"-Fa${CMAKE_CURRENT_SOURCE_DIR}/main.asm -FA")
add_executable(${SAMPLE_NAME} code.c main.c)
add_test( 
	NAME ${SAMPLE_NAME}
	COMMAND $<TARGET_FILE:${SAMPLE_NAME}>)