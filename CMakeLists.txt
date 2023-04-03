cmake_minimum_required(VERSION 3.10.2)
project (netcalc)

# SETTINGS
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
file(GLOB SOURCES src/*.cpp)

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "Build type not specified: Use Release by default")
    set(CMAKE_BUILD_TYPE Release)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/release)

elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Build type: Release")
    set(CMAKE_BUILD_TYPE Release)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/release)

elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Build type: Debug")
    set(CMAKE_BUILD_TYPE Debug)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/debug)

endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# PROGRAM
add_executable(netcalc ${SOURCES})
install(TARGETS netcalc RUNTIME DESTINATION bin)