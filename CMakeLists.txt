cmake_minimum_required(VERSION 2.8)

set(TOP_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_CXX_FLAGS $ENV{CXX_FLAGS})
set(CMAKE_C_FLAGS $ENV{C_FLAGS})

if($ENV{MAKE_DEBUG_MODE})
	set(CMAKE_VERBOSE_MAKEFILE true)
endif()

add_subdirectory(bfgi_lib)
add_subdirectory(bfgi)
