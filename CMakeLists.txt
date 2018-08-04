cmake_minimum_required(VERSION 3.5)

if(NOT TARGET Atic)
	add_library(Atic INTERFACE)

	target_include_directories(Atic INTERFACE include)
endif()
