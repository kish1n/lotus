#version 440 core
out vec4 FragColor;

in vec3 FragPos;

void main()
{
    float goal = -0.2 * FragPos.x + 0.5;
    if (FragPos.y > goal)
    {
        FragColor = vec4(1f, 0f, 0f, 1f);
    }
    else
    {
        FragColor = vec4(0f, 1f, 0f, 1f);
    }
}