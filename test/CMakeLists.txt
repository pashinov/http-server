#----------------------------------------------------------
# GTest
#----------------------------------------------------------
set(GOOGLETEST_ROOT external/googletest/googletest CACHE STRING "Google Test source root")

include_directories(
        ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}
        ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/include)

set(GOOGLETEST_SOURCES
        ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest-all.cc
        ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest_main.cc
        )

foreach(_source ${GOOGLETEST_SOURCES})
    set_source_files_properties(${_source} PROPERTIES GENERATED 1)
endforeach()

add_library(gtest ${GOOGLETEST_SOURCES})

include_directories(
        ${GTEST_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}/include)

set(TEST_SRC_FILES
        test_conf_manager.cpp
        test_safe_queue.cpp
        )

foreach(_test_file ${TEST_SRC_FILES})
    get_filename_component(_test_name ${_test_file} NAME_WE)
    add_executable(${_test_name} ${_test_file} ${SRC_FILES})
    target_link_libraries(${_test_name} gtest pthread yaml-cpp ${Boost_LIBRARIES})
    add_test(${_test_name} ${_test_name})
endforeach()

#----------------------------------------------------------
# Code Coverage
#----------------------------------------------------------
if(CMAKE_COMPILER_IS_GNUCXX)
    foreach(_test_file ${TEST_SRC_FILES})
        get_filename_component(_test_name ${_test_file} NAME_WE)
        set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
        include(CodeCoverage)
        APPEND_COVERAGE_COMPILER_FLAGS()
        setup_target_for_coverage(NAME ${_test_name}_coverage EXECUTABLE ${_test_name})
    endforeach()
endif()
#----------------------------------------------------------
