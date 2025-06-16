#version 440 core
out vec4 FragColor;

in vec3 FragPos;

void main()
{
    float goal = FragPos.x;
    if (FragPos.y > goal)
    {
        FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
    }
    else
    {
        FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);
    }
}