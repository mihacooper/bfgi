set( TARGET_NAME bfgi )

include_directories( BEFORE
                     ${CMAKE_CURRENT_SOURCE_DIR} 
					 ${TOP_DIR}/bfgi_lib
					)

file( GLOB HEADER_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h *.hpp )
file( GLOB SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.c *.cpp *.cc )

add_executable (${TARGET_NAME} ${SOURCE_FILES})

set(EXECUTABLE_OUTPUT_PATH $ENV{BIN_DIRECTORY})

target_link_libraries( ${TARGET_NAME} bfgl)
