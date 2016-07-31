#version 430 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 velocity;
layout(location = 2) in vec4 force;
layout(location = 3) in vec4 size;
layout(location = 4) in vec4 color;

out vec4 vSize;
out vec4 vColor;

void main()
{
	gl_Position = position;
	vSize = size;
	vColor = color;
}
