set(CMAKE_CXX_STANDARD 26)
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD
  # This specific value changes as experimental support evolves. See
  # `Help/dev/experimental.rst` in the CMake source corresponding to
  # your CMake build for the exact value to use.
  "d0edc3af-4c50-42ea-a356-e2862fe7a444")
set(CMAKE_TOOLCHAIN_FILE $ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake CACHE FILEPATH "The cmake toolchain file")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
string(REPLACE "\\" "/" CMAKE_TOOLCHAIN_FILE ${CMAKE_TOOLCHAIN_FILE})
set(CMAKE_CXX_MODULE_STD 1)
