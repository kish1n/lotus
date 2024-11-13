find_package(OpenGL REQUIRED)

add_library(Glad STATIC
    Glad/glad.c
)

target_include_directories(Glad 
    PUBLIC
        Glad/include
)