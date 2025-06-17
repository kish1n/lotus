# lotus
Repository for the Lotus 2D game engine

Basic Setup for Windows:
1. Install llvm-mingw (https://github.com/mstorsjo/llvm-mingw)
2. Setup PATH
3. cmake -G Ninja -B build .
4. cd build
5. ninja \<target>

Current available targets:
`lotus`, `playground`, `brick-breaker`

Tech: C++23, OpenGL w/ GLSL, SDL3
