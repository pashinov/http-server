cmake_minimum_required(VERSION 3.1)

project(http-server VERSION 1.0.2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(WITH_TESTS "Enable Unit Tests" OFF)

option(WITH_ASAN "Build with Address Sanitizer" OFF)
option(WITH_TSAN "Build with Threads Sanitizer" OFF)
option(WITH_MSAN "Build with Memory Sanitizer" OFF)


set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" AND USE_CLANG_LIBCPP)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

if(WITH_TSAN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread -g -O2 -fPIC -pie")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=thread -g -O2 -fPIC -pie")
endif()

if(WITH_ASAN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fsanitize=address -fno-omit-frame-pointer -O1")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -fsanitize=address -fno-omit-frame-pointer -O1")
endif()

if(WITH_MSAN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=memory -fno-omit-frame-pointer -g")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=memory -fno-omit-frame-pointer -g")
endif()

# location of source files
aux_source_directory( ${CMAKE_CURRENT_SOURCE_DIR}/src SRC_FILES )
aux_source_directory( ${CMAKE_CURRENT_SOURCE_DIR}/src/application SRC_FILES )
aux_source_directory( ${CMAKE_CURRENT_SOURCE_DIR}/src/common SRC_FILES )
aux_source_directory( ${CMAKE_CURRENT_SOURCE_DIR}/src/conf_manager SRC_FILES )
aux_source_directory( ${CMAKE_CURRENT_SOURCE_DIR}/src/delegate SRC_FILES )
aux_source_directory( ${CMAKE_CURRENT_SOURCE_DIR}/src/http_server SRC_FILES )
aux_source_directory( ${CMAKE_CURRENT_SOURCE_DIR}/src/logger SRC_FILES )
aux_source_directory( ${CMAKE_CURRENT_SOURCE_DIR}/src/thread_raii SRC_FILES )

include_directories(include)

find_package(Boost COMPONENTS system program_options REQUIRED)
include_directories(${BOOST_INCLUDE_DIRS})

add_executable(http-server ${SRC_FILES})

target_link_libraries(${PROJECT_NAME}
        pthread
        yaml-cpp
        ${Boost_LIBRARIES})

if(WITH_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()

# create log directory
set(log_directory "/var/log/${PROJECT_NAME}")
install(CODE "FILE(MAKE_DIRECTORY ${log_directory})")

# install scripts
set(project_scripts ${CMAKE_CURRENT_SOURCE_DIR}/scripts/${PROJECT_NAME})
set(scripts_install_dir "/etc/init.d")
install(FILES "${project_scripts}"
        PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
        DESTINATION "${scripts_install_dir}")

# install config
set(project_config ${CMAKE_CURRENT_SOURCE_DIR}/config/http-server.yaml)
set(config_install_dir "/etc/http-server")
install(CODE "FILE(MAKE_DIRECTORY ${config_install_dir})")
install(FILES "${project_config}" DESTINATION "${config_install_dir}")

# install web
set(html_directory "/var/www/html")
set(index_html ${CMAKE_CURRENT_SOURCE_DIR}/html/index.html)
install(CODE "FILE(MAKE_DIRECTORY ${html_directory})")
install(FILES "${index_html}" DESTINATION "${html_directory}")

# install target
set(CMAKE_INSTALL_PREFIX /usr/local)
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

# uninstall target
configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Uninstall.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
        IMMEDIATE @ONLY
)

add_custom_target(uninstall COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
