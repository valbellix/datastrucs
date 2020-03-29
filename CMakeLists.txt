cmake_minimum_required(VERSION 3.10)

project(datastructs C)

add_library(libdatastructs STATIC
	src/vect.c
)

target_include_directories(libdatastructs
	PRIVATE
		include/ds
)

add_executable(test
	tests/test.c
)

target_include_directories(libdatastructs
	PUBLIC
		include)

target_link_libraries(test
	PRIVATE
		libdatastructs
)
