set(CMAKE_CXX_STANDARD 26)
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD
  # This specific value changes as experimental support evolves. See
  # `Help/dev/experimental.rst` in the CMake source corresponding to
  # your CMake build for the exact value to use.
  "a9e1cf81-9932-4810-974b-6eccaf14e457")
set(CMAKE_TOOLCHAIN_FILE $ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake CACHE FILEPATH "The cmake toolchain file")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
string(REPLACE "\\" "/" CMAKE_TOOLCHAIN_FILE ${CMAKE_TOOLCHAIN_FILE})
set(CMAKE_CXX_MODULE_STD 1)


# hack to get intellisense to work
get_filename_component(COMPILER_DIR "${CMAKE_CXX_COMPILER}" DIRECTORY)
get_filename_component(LLVM_ROOT "${COMPILER_DIR}" DIRECTORY)
message(STATUS "LLVM root: ${LLVM_ROOT}")

add_library(unused_std_target STATIC)

target_sources(unused_std_target
        PRIVATE
        FILE_SET CXX_MODULES
        BASE_DIRS ${LLVM_ROOT}/share/libc++/v1
        FILES ${LLVM_ROOT}/share/libc++/v1/std.cppm ${LLVM_ROOT}/share/libc++/v1/std.compat.cppm)
