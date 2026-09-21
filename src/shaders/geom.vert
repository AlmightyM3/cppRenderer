#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aTex;

out vec2 texCoord;
out vec3 fragPos;
out vec3 normal;

uniform mat4 camera;
uniform mat4 transform;

void main()
{
	gl_Position = camera * transform * vec4(aPos, 1.0f);
	fragPos = gl_Position.xyz;
	texCoord = aTex;
	normal = aNorm;
}