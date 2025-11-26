cmake_minimum_required(VERSION 3.30)

include(cmake/toolchain.cmake)

project(lotus VERSION 0.1.0)

#[[
# hack to get intellisense to work
add_library(unused_std_target STATIC EXCLUDE_FROM_ALL)

target_sources(unused_std_target
        PRIVATE
        FILE_SET CXX_MODULES
        BASE_DIRS /usr/share/libc++/v1
        FILES /usr/share/libc++/v1/std.cppm /usr/share/libc++/v1/std.compat.cppm)
        ]]

find_package(SDL3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Stb REQUIRED)

add_subdirectory(lotus)
add_subdirectory(external)
add_subdirectory(games)
