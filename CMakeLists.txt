cmake_minimum_required(VERSION 3.10)

project(datastructs C)

set("SOURCE_FILES"
	src/ds/vect.c
	src/ds/list.c
	src/ds/bst.c
	src/ds/treemap.c
)

add_library(datastructs STATIC ${SOURCE_FILES})

target_include_directories(datastructs
	PRIVATE
		src/ds
)

# I MSVC complaints a lot... need to understand the cause...
if (!MSVC)
	add_library(datastructsShared SHARED ${SOURCE_FILES})
	set_target_properties(datastructsShared
		PROPERTIES OUTPUT_NAME
			datastructs
	)
	target_include_directories(datastructsShared
		PRIVATE
			src/ds
	)
endif()

add_executable(test
	tests/test.c
)

target_include_directories(datastructs
	PUBLIC
		src)

target_include_directories(test
	PRIVATE
		tests
)

set("TEST_LIBS" "m")

if (MSVC)
	set("TEST_LIBS" "")
endif()

target_link_libraries(test
	PRIVATE
		datastructs
		${TEST_LIBS}
)

