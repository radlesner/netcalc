cmake_minimum_required(VERSION 2.8.9)
project (netcalc)

# LANGUAGE SET
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic")

# PROGRAM
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(SOURCES ${SOURCE_DIR}/main.cpp
            ${SOURCE_DIR}/check_ip.cpp
            ${SOURCE_DIR}/check_prefix.cpp
            ${SOURCE_DIR}/convert_numbers.cpp
            ${SOURCE_DIR}/ip_operations.cpp
            ${SOURCE_DIR}/netmask.cpp
            ${SOURCE_DIR}/octet.cpp
            ${SOURCE_DIR}/output.cpp
            ${SOURCE_DIR}/get_network_addresses.cpp
            )

add_executable(netcalc ${SOURCES})

install(TARGETS netcalc RUNTIME DESTINATION bin)