cmake_minimum_required(VERSION 3.15)

project(props LANGUAGES CXX VERSION 1.0.0)

#option(PROPS_USE_EMBEDDED_JSON "Use the shipped json header if not available on the system" ON)
option(PROPS_INSTALL "Generate install targets for props" ON)
option(PROPS_EXPORT "Export the current build tree to the package registry" ON)
option(BUILD_TESTING "Build unit tests" ON)
#option(BUILD_BENCHMARK "Build benchmark" OFF)
option(CODE_COVERAGE "Generate code coverage data" ON)
#option(COVERALLS "Generate coveralls data" OFF)

set(PROPS_INSTALL_INCLUDE_DIR "include")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

if(CMAKE_COMPILER_IS_GNUCC)
    add_compile_options(-Wall)
endif()

if (CODE_COVERAGE)
    if("${CMAKE_C_COMPILER_ID}" MATCHES "(Apple)?[Cc]lang" OR "${CMAKE_CXX_COMPILER_ID}" MATCHES "(Apple)?[Cc]lang")
        message("Building with llvm Code Coverage Tools")
        add_compile_options(-fprofile-instr-generate -fcoverage-mapping)
        add_link_options(-fprofile-instr-generate -fcoverage-mapping)
    elseif(CMAKE_COMPILER_IS_GNUCXX)
        message("Building with gcov Code Coverage Tools")
        add_compile_options(--coverage)
        add_link_options(--coverage)
    endif()
endif()

if(MSVC)
    add_compile_options(/W4 /permissive- /utf-8 /Zc:__cplusplus)
endif()


add_library(props INTERFACE)
add_library(daball::props ALIAS props)

target_include_directories(props INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${PROPS_INSTALL_INCLUDE_DIR}>
        )

target_compile_features(props INTERFACE cxx_std_17)

if(BUILD_TESTING)
    enable_testing()
    find_package(Boost 1.71.0 REQUIRED COMPONENTS locale log unit_test_framework) #math)
    file(GLOB_RECURSE TEST_SRCS LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} tests/src/*.cpp)
    foreach(testSrc ${TEST_SRCS})
        get_filename_component(testName ${testSrc} NAME_WE)
        message("Discovered ${testName} build test.")
        add_executable(${testName} ${testSrc})
        target_compile_features(${testName} INTERFACE cxx_std_17)
        target_link_libraries(${testName} PRIVATE props ${Boost_LIBRARIES})
        add_test(${testName} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${testName})
    endforeach(testSrc)

#    add_executable(props_test
#            test/unit.cpp
#            test/unit-files.cpp
#            test/unit-renderer.cpp
#            )
#    target_link_libraries(props_test PRIVATE props)
#
#    add_test(props_test ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/props_test)
#
#
#    add_library(single_props INTERFACE)
#    target_compile_features(single_props INTERFACE cxx_std_11)
#    target_include_directories(single_props INTERFACE single_include include third_party/include)
#
#    add_executable(single_props_test
#            test/unit.cpp
#            test/unit-files.cpp
#            test/unit-renderer.cpp
#            )
#    target_link_libraries(single_props_test PRIVATE single_props)
#
#    add_test(single_props_test ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/single_props_test)
endif()

#if(COVERALLS)
#    include(Coveralls)
#    coveralls_turn_on_coverage()
#
#    file(GLOB_RECURSE COVERAGE_SRCS include/props/*.hpp)
#
#    # set(COVERAGE_SRCS test/unit.cpp test/unit-renderer.cpp include/props)
#
#    coveralls_setup("${COVERAGE_SRCS}" OFF) # If we should upload.
#endif()

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/propsConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
)


## build tree package config
#configure_file(
#        cmake/config/propsBuildConfig.cmake.in
#        propsConfig.cmake
#        @ONLY
#)
#
#
install(TARGETS props EXPORT propsTargets)
#
#
export(
        EXPORT propsTargets
        NAMESPACE daball::
        FILE "${CMAKE_CURRENT_BINARY_DIR}/propsTargets.cmake"
)

## build tree package config
#configure_file(
#        cmake/config/propsBuildConfig.cmake.in
#        propsConfig.cmake
#        @ONLY
#)
#

if(PROPS_INSTALL)
    set(PROPS_CONFIG_PATH "lib/cmake/props")

    # install tree package config
    configure_package_config_file(
            cmake/propsConfig.cmake.in
            ${PROPS_CONFIG_PATH}/propsConfig.cmake
            INSTALL_DESTINATION ${PROPS_CONFIG_PATH}
            NO_CHECK_REQUIRED_COMPONENTS_MACRO
    )

    install(DIRECTORY include/daball/props DESTINATION ${PROPS_INSTALL_INCLUDE_DIR} FILES_MATCHING PATTERN "*.hpp")
#    install(FILES
#            "${CMAKE_CURRENT_SOURCE_DIR}/third_party/include/nlohmann/json.hpp"
#            "${CMAKE_CURRENT_SOURCE_DIR}/third_party/include/nlohmann/LICENSE.MIT"
#            DESTINATION "${PROPS_INSTALL_INCLUDE_DIR}/props"
#            )

    install(
            FILES
            "${CMAKE_CURRENT_BINARY_DIR}/${PROPS_CONFIG_PATH}/propsConfig.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/propsConfigVersion.cmake"
            DESTINATION ${PROPS_CONFIG_PATH}
    )

    install(
            EXPORT propsTargets FILE propsTargets.cmake
            NAMESPACE daball::
            DESTINATION ${PROPS_CONFIG_PATH}
    )
endif()


if(PROPS_EXPORT)
    export(PACKAGE props)
endif()
