#version 410 core

out vec4 FragColor;

in vec2 screenPos;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;

void main()
{
    FragColor = vec4(texture(gAlbedoSpec, screenPos).rgb, 1.0f);
}