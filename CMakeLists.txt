cmake_minimum_required(VERSION 3.10.2)
project (netcalc)

# SETTINGS
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
file(GLOB SOURCES src/*.c src/gtk/*.c)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

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

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic")
set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Icon
set(APPLICATIONS_DIR "/usr/share/applications/")
set(ICON_DIR "/usr/share/icons/hicolor/")

# PROGRAM
add_executable(netcalc ${SOURCES})

target_include_directories(netcalc PUBLIC ${GTK3_INCLUDE_DIRS})
target_compile_options(netcalc PUBLIC ${GTK3_CFLAGS_OTHER})
target_link_libraries(netcalc ${GTK3_LIBRARIES})

install(TARGETS netcalc RUNTIME DESTINATION bin)
install(FILES resources/netcalc.desktop DESTINATION ${APPLICATIONS_DIR})
install(FILES resources/netcalc-128x128.png DESTINATION ${ICON_DIR}/128x128/apps/)