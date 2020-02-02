enable_testing()
find_package(Boost 1.71.0 REQUIRED COMPONENTS locale log unit_test_framework) #math)
#message("trace: ${daball_props_DIR}")
#set(CMAKE_PREFIX_PATH ${daball_props_DIR})
find_package(props 1.0.0 CONFIG REQUIRED)

#include_directories(BEFORE "${CMAKE_CURRENT_SOURCE_DIR}/../include" "${CMAKE_CURRENT_SOURCE_DIR}/../ccc/src")

#Run through each test source file
file(GLOB_RECURSE TEST_SRCS LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.cpp)
foreach(testSrc ${TEST_SRCS})
    get_filename_component(testName ${testSrc} NAME_WE)
    message("Discovered ${testName}.")
#    target_include_directories(${testName}) #daball::props)
    target_link_libraries(${testName} ${Boost_LIBRARIES})

    #    if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    #        conan_target_link_libraries(${testName})
    #    endif()

    target_include_directories(${testName} PUBLIC
            "${PROJECT_BINARY_DIR}"
            "${CMAKE_CURRENT_SOURCE_DIR}/src"
            )

    set_target_properties(${testName} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_TEST_OUTPUT_DIRECTORY})

    add_test(NAME ${testName}
            COMMAND ${PROJECT_BINARY_DIR}/tests/${testName}
            WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/tests
            )
endforeach(testSrc)