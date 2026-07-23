#version 410 core

layout (location = 0) in vec3 aPos;

out vec2 screenPos;

void main()
{
	gl_Position = vec4(aPos, 1.0f);
	screenPos = aPos.xy/2.0f + 0.5f;
}