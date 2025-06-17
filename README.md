# lotus
Repository for the Lotus 2D game engine

Basic Setup for Windows:
1. Install llvm-mingw (https://github.com/mstorsjo/llvm-mingw)
2. Install cmake version 4.0.2 (import std experimental uuid may be different on other versions)
3. Setup PATH
4. cmake -G Ninja -B build .
5. cd build
6. ninja \<target>

Current available targets:
`lotus`, `playground`, `brick-breaker`

Tech: C++23, OpenGL w/ GLSL, SDL3
