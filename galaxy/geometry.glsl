#version 450 core

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

uniform mat4 projectionMatrix;

in vec3 vColor[];
out vec3 gColor;

void main(void)
{
	const vec4 position = gl_in[0].gl_Position;
	const vec3 color = vColor[0];

	gColor = color;

	gl_Position = projectionMatrix * (position + vec4(-10, -10, 0, 0));
	EmitVertex();

	gl_Position = projectionMatrix * (position + vec4(-10, 10, 0, 0));
	EmitVertex();

	gl_Position = projectionMatrix * (position + vec4(10, -10, 0, 0));
	EmitVertex();

	gl_Position = projectionMatrix * (position + vec4(10, 10, 0, 0));
	EmitVertex();

	EndPrimitive();
}
