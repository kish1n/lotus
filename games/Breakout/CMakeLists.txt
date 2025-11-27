add_executable(Breakout main.cpp)

target_link_libraries(Breakout
    PRIVATE
        lotus
        SDL3::SDL3
        Glad
)