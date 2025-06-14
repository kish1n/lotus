cmake_minimum_required(VERSION 3.30)

include(cmake/toolchain.cmake)

project(lotus VERSION 0.1.0)

# hack to get intellisense to work
get_filename_component(COMPILER_DIR "${CMAKE_CXX_COMPILER}" DIRECTORY)
get_filename_component(LLVM_ROOT "${COMPILER_DIR}" DIRECTORY)
message(STATUS "LLVM root: ${LLVM_ROOT}")

add_library(unused_std_target STATIC EXCLUDE_FROM_ALL)

target_sources(unused_std_target
        PRIVATE
        FILE_SET CXX_MODULES
        BASE_DIRS ${LLVM_ROOT}/share/libc++/v1
        FILES ${LLVM_ROOT}/share/libc++/v1/std.cppm ${LLVM_ROOT}/share/libc++/v1/std.compat.cppm)

find_package(SDL3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Stb REQUIRED)

add_subdirectory(lotus)
add_subdirectory(external)
add_subdirectory(games)
