cmake_minimum_required(VERSION 3.10)

project(datastructs C)

add_library(datastructs STATIC
	src/ds/vect.c
	src/ds/list.c
)

target_include_directories(datastructs
	PRIVATE
		src/ds
)

add_executable(test
	tests/test.c
)

target_include_directories(datastructs
	PUBLIC
		src)

target_link_libraries(test
	PRIVATE
		datastructs
)
