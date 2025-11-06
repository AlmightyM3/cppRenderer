#version 410 core

out vec4 FragColor;

layout (location = 0) in vec2 texCoord;

uniform sampler2D testImg;

void main()
{
    FragColor = vec4(texture(testImg, texCoord).rgb, 1.0f);
}