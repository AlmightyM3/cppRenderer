#version 410 core

out vec4 FragColor;
layout (location = 0) in vec3 color;

void main()
{
    FragColor = vec4(color, 1.0f);
}