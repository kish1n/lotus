add_library(lotus)

target_sources(lotus
    PRIVATE
        src/stb_image.cpp
        src/State.cpp
)

target_sources(lotus
        PUBLIC
    FILE_SET lotus_modules
    TYPE CXX_MODULES
    FILES
        interface/base.ixx
        interface/GameLoop.ixx
        interface/GameObject.ixx
        interface/mesh_engine.ixx
        interface/programs.ixx
        interface/render.ixx
        interface/RenderManager.ixx
        interface/State.ixx
        interface/lotus.ixx

        PRIVATE
        src/GameLoop.cpp
        src/programs.cpp
        src/render.cpp
        src/RenderManager.cpp
)

target_include_directories(lotus
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
