#version 450 core

layout(location = 0) in vec2 position;
layout(location = 1) in float size;
layout(location = 2) in vec4 color;

out float vSize;
out vec4 vColor;

void main()
{
	gl_Position = vec4(position, 0.0f, 1.0f);
	vSize = size;
	vColor = color;
}
