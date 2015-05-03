set( TARGET_NAME bfgl )

include_directories( BEFORE
                     ${CMAKE_CURRENT_SOURCE_DIR} 
					)


file( GLOB_RECURSE HEADER_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h *.hpp )
file( GLOB_RECURSE SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.c *.cpp *.cc )

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/kernels")

add_library(${TARGET_NAME} SHARED ${SOURCE_FILES})

target_link_libraries( ${TARGET_NAME} m )

set(LIBRARY_OUTPUT_PATH $ENV{LIBRARY_DIRECTORY})
