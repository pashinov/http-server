# assembly file

# stop if cmake version below 3.7.2
cmake_minimum_required( VERSION 3.7.2 FATAL_ERROR)

# choice of standard
set_target_properties( ${TARGET} PROPERTIES
		CXX_STANDARD 17
		CXX_STANDARD_REQUIRED YES
		CXX_EXTENSIONS NO
		)

# compilation flags
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DLINUX" )

# PROJECT
set ( PROJECT server )

# project name
project ( ${PROJECT} )

# project version
set( VERSION_MAJOR 1 )
set( VERSION_MINOR 0 )

# output folder for binaries
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} )

# location of header files
include_directories( "inc"
		"inc/common"
		"inc/logger"
		)

# location of source files
aux_source_directory( src SOURCES )
aux_source_directory( src/common SOURCES )
aux_source_directory( src/logger SOURCES )

# build executable
add_executable( ${PROJECT} ${SOURCES} )

# link process
target_link_libraries( ${PROJECT} )
