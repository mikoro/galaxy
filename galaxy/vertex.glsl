#version 450 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec3 color;

uniform mat4 viewMatrix;

out vec3 colorVarying;

void main()
{
	gl_Position = viewMatrix * vec4(position, 0.0f, 1.0f);
	colorVarying = color;
}
