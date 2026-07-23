#version 410 core

out vec4 FragColor;

in vec2 screenPos;

void main()
{
    FragColor = vec4(screenPos, 0.0f, 1.0f);
}