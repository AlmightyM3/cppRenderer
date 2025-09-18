#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 0) out vec3 color;

uniform float time;

void main()
{
	gl_Position = vec4(aPos, 1.0f);
	color = vec3(aPos.xy, sin(time*1.5f)*0.5f) + 0.5f;
}