cmake_minimum_required(VERSION 3.27.2)

include(cmake/toolchain.cmake)

project(lotus VERSION 0.1.0)

find_package(SDL3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Stb REQUIRED)

add_subdirectory(lotus)
add_subdirectory(external)
add_subdirectory(games)
