cmake_minimum_required(VERSION 3.5)

if(NOT TARGET Atic)
	set(CMAKE_CXX_COMPILE clang++-6.0)
	set(CMAKE_CXX_STANDARD 17)

	file(GLOB_RECURSE Atic_SRC PRIVATE src/*.cc)

	include_directories(include)
	add_library(Atic SHARED ${Atic_SRC})

	target_include_directories(Atic
		INTERFACE include
		PRIVATE src
	)
endif()
