set(NAME MISC)

file(GLOB ROOT_SOURCE *.cpp)
file(GLOB ROOT_INLINE *.inl)
file(GLOB ROOT_HEADER *.hpp)

add_executable(${NAME} ${ROOT_SOURCE} ${ROOT_INLINE} ${ROOT_HEADER})