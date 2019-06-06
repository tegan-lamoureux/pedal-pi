cmake_minimum_required(VERSION 3.2.0)

project(PedalPi C CXX)

set(target_name "pedal")

# Target Names
set(app "${target_name}")
set(tests "${target_name}_unit_tests")


#################
#### Source Files

set(
    app_sources

    # Headers
    src/distortion.h
    src/echo.h

    # Sources
    src/distortion.cpp
    src/echo.cpp
)

set(
    tests_sources

    ${app_sources}

    tests/jack_tests.cpp
    tests/distortion_tests.cpp
    tests/echo_tests.cpp
)


##############
#### Libraries

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/external_libraries")

find_package(JACK REQUIRED)
if (JACK_FOUND)
    include_directories(JACK_INCLUDE_DIR)
endif()

######################
#### Google Test Setup
#
# Downloads GTest from Google at configure time, and builds it at
# project compile time in the build directory. 

include(GoogleTest)


###################
#### Build Main App

set(CMAKE_CXX_STANDARD 17)

add_executable(
    ${app}

    src/main.cpp
    ${app_sources}
)

target_link_libraries(
    ${app}
    ${JACK_LIBRARY}
)


################
#### Build Tests

add_executable(
    ${tests}

    ${tests_sources}
)

target_include_directories(
    ${tests} PUBLIC

    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(
    ${tests}

    gtest_main
    ${JACK_LIBRARY}
)

