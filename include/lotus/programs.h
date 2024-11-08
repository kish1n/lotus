#pragma once

inline const char *vertexShaderSource = R"(
#version 440 core
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)";

inline const char *fragmentShaderSource = R"(
#version 440 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
)";

unsigned int compileBasicProgram();
