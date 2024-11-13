cmake_minimum_required(VERSION 3.28.3)

include(cmake/toolchain.cmake)

project(lotus VERSION 0.1.0)

find_package(SDL3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Stb REQUIRED)

add_executable(lotus)

target_sources(lotus
    PRIVATE
        src/main.cpp
        src/render.cpp
        src/game.cpp
        src/programs.cpp
)

target_include_directories(lotus
    PRIVATE
        include
        ${Stb_INCLUDE_DIR}
        external/Glad/include
)

target_link_libraries(lotus
    PRIVATE
        SDL3::SDL3
        glm::glm
        Glad
)

add_subdirectory(external)
