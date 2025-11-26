add_library(lotus)

target_sources(lotus
    PRIVATE
    src/Game.cpp
    src/playground.cpp
    src/ResourceManager.cpp
    src/Shader.cpp
    src/stb_image.cpp
    src/Texture.cpp
)

target_include_directories(lotus
    PUBLIC
        include
    PRIVATE
        ${Stb_INCLUDE_DIR}
        ${CMAKE_SOURCE_DIR}/external/Glad/include
)

target_link_libraries(lotus
    PRIVATE
        SDL3::SDL3
        glm::glm
        Glad
)

add_custom_target(copy_content
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
    ${CMAKE_SOURCE_DIR}/Content
    $<TARGET_FILE_DIR:lotus>/Content
    COMMENT "Copying content to build directory"
)

add_dependencies(lotus copy_content)

### Playground executable ###

add_executable(playground
    src/playground.cpp
)

target_link_libraries(playground
    PRIVATE
        lotus
)
