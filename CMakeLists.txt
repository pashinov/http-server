# assembly file

# stop if cmake version below 3.7.2
cmake_minimum_required( VERSION 3.7.2 FATAL_ERROR)

# choice of standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# project variable
set ( PROJECT_NAME server )

# project name
project ( ${PROJECT_NAME} )

# output folder for binaries
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} )

################################
# Code Coverage
################################
set( CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake )

include( CodeCoverage )
setup_target_for_coverage( ${PROJECT_NAME}_coverage ${PROJECT_NAME} coverage )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage" )
###############################


################################
# GTest
################################
set( GOOGLETEST_ROOT external/googletest/googletest CACHE STRING "Google Test source root" )

include_directories(
        ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}
        ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/include
)

set( GOOGLETEST_SOURCES
        ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest-all.cc
        ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest_main.cc )

foreach( _source ${GOOGLETEST_SOURCES} )
    set_source_files_properties( ${_source} PROPERTIES GENERATED 1 )
endforeach()

add_library( gtest ${GOOGLETEST_SOURCES} )

include_directories(
        inc/common
        inc/conf_manager
        inc/safe_queue
        ${GTEST_INCLUDE_DIRS}
)

# location of source test files
aux_source_directory( tests SOURCES_TEST )
aux_source_directory( src/conf_manager SOURCES_TEST )

add_executable( GoogleTest ${SOURCES_TEST} )
target_link_libraries( GoogleTest gtest pthread yaml-cpp )

enable_testing()
add_test( GoogleTest GoogleTest )
################################


# location of header files
include_directories( "inc"
        "inc/application"
        "inc/conf_manager"
        "inc/common"
        "inc/delegate"
        "inc/http_server"
        "inc/logger"
        "inc/safe_queue"
        "inc/thread_raii"
        )

# location of source files
aux_source_directory( src SOURCES )
aux_source_directory( src/application SOURCES )
aux_source_directory( src/common SOURCES )
aux_source_directory( src/conf_manager SOURCES )
aux_source_directory( src/delegate SOURCES )
aux_source_directory( src/http_server SOURCES )
aux_source_directory( src/logger SOURCES )
aux_source_directory( src/thread_raii SOURCES )

# build executable
add_executable( ${PROJECT_NAME} ${SOURCES} )

# link process
target_link_libraries( ${PROJECT_NAME} pthread yaml-cpp boost_system)

# create log directory
set( log_directory "/var/log/${PROJECT_NAME}" )
install( CODE "FILE(MAKE_DIRECTORY ${log_directory})" )

# install scripts
set( project_scripts ${CMAKE_CURRENT_SOURCE_DIR}/scripts/${PROJECT_NAME} )
set( scripts_install_dir "/etc/init.d" )
install( FILES "${project_scripts}"
        PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
        DESTINATION "${scripts_install_dir}" )

# install config
set( project_config ${CMAKE_CURRENT_SOURCE_DIR}/config/server.yaml )
set( config_install_dir "/etc/server" )
install( CODE "FILE(MAKE_DIRECTORY ${config_install_dir})" )
install( FILES "${project_config}" DESTINATION "${config_install_dir}" )

# install web
set( html_directory "/var/www/html" )
set( index_html ${CMAKE_CURRENT_SOURCE_DIR}/html/index.html )
install( CODE "FILE(MAKE_DIRECTORY ${html_directory})" )
install( FILES "${index_html}" DESTINATION "${html_directory}" )

# install target
set( CMAKE_INSTALL_PREFIX /usr/local )
install( TARGETS ${PROJECT_NAME} DESTINATION bin )

# uninstall target
configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Uninstall.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
        IMMEDIATE @ONLY
)

add_custom_target( uninstall COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake )
