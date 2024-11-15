#version 440 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;
in vec3 NDCCoord;

uniform sampler2D ourTexture;
uniform vec2 ourPoint;

void main()
{
    float xd = NDCCoord.x - ourPoint.x;
    float yd = NDCCoord.y - ourPoint.y;
    float d = xd * xd + yd * yd;
    float a = 1 - clamp(64 * d * d, 0, 1);
    vec4 color = texture(ourTexture, TexCoord);
    FragColor = vec4(color.xyz, a);
}