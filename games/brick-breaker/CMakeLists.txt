add_executable(brick-breaker)

target_sources(brick-breaker
    PRIVATE
        src/main.cpp
)

target_link_libraries(brick-breaker
    PRIVATE
        lotus
)