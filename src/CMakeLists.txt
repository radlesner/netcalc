cmake_minimum_required(VERSION 2.8.9)
project (netcalc)

set(SOURCES main.cpp
            check_ip.cpp
            check_prefix.cpp
            convert_numbers.cpp
            ip_operations.cpp
            netmask.cpp
            octet.cpp
            )

add_executable(netcalc ${SOURCES})