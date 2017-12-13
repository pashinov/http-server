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

# project variable
set ( PROJECT_NAME server )

# project name
project ( ${PROJECT_NAME} )

# project version
set( VERSION_MAJOR 1 )
set( VERSION_MINOR 0 )

# output folder for binaries
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} )

# location of header files
include_directories( "inc"
        "inc/conf_manager"
        "inc/common"
        "inc/daemon"
        "inc/delegate"
        "inc/logger"
        "inc/safe_queue"
        "inc/thread_raii"
        )

# location of source files
aux_source_directory( src SOURCES )
aux_source_directory( src/common SOURCES )
aux_source_directory( src/conf_manager SOURCES )
aux_source_directory( src/daemon SOURCES )
aux_source_directory( src/delegate SOURCES )
aux_source_directory( src/logger SOURCES )
aux_source_directory( src/thread_raii SOURCES )

# build executable
add_executable( ${PROJECT_NAME} ${SOURCES} )

# link process
target_link_libraries( ${PROJECT_NAME} -pthread -lyaml-cpp )

# create log directory
set( log_directory "/var/log/${PROJECT_NAME}")
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

# install target
set( CMAKE_INSTALL_PREFIX /usr/local )
install( TARGETS ${PROJECT_NAME} DESTINATION bin )

# uninstall target
configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Uninstall.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
        IMMEDIATE @ONLY)

add_custom_target(uninstall COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
