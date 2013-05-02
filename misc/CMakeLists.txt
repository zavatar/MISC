set(NAME MISC)

file(GLOB ROOT_SOURCE *.cpp)
file(GLOB ROOT_INLINE *.inl)
file(GLOB ROOT_HEADER *.hpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

add_executable(${NAME} 
	${ROOT_SOURCE}    ${ROOT_INLINE}    ${ROOT_HEADER})