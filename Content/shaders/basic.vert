#version 440 core
layout (location = 0) in vec3 aPos;

out vec4 VertColor;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    if (aPos.x > 0.15)
        VertColor = vec4(0.0, 1.0, 0.0, 1.0); // Green color
    else if (aPos.x < -0.05)
        VertColor = vec4(1.0, 0.0, 0.0, 1.0); // Red color
    else
        VertColor = vec4(0.0, 0.0, 1.0, 1.0); // Blue color
}