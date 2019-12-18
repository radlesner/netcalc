cmake_minimum_required(VERSION 2.8.9)
project (netcalc)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SOURCES ${SOURCE_DIR}/main.cpp
            ${SOURCE_DIR}/check_ip.cpp
            ${SOURCE_DIR}/convert_numbers.cpp
            ${SOURCE_DIR}/ip_operations.cpp
            ${SOURCE_DIR}/netmask.cpp
            ${SOURCE_DIR}/octet.cpp
            )

add_executable(netcalc ${SOURCES})