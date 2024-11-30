cmake_minimum_required(VERSION 3.27.2)

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
        src/programs.cpp
        src/stb_image.cpp
        src/RenderManager.cpp
        src/GameLoop.cpp
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

add_custom_target(copy_content
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
    ${CMAKE_SOURCE_DIR}/Content
    $<TARGET_FILE_DIR:lotus>/Content
    COMMENT "Copying content to build directory"
)

add_dependencies(lotus copy_content)
