#version 450 core

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

uniform mat4 projectionMatrix;

in float vSize[];
in vec4 vColor[];

out vec2 gTexCoord;
out vec4 gColor;

void main(void)
{
	const vec4 position = gl_in[0].gl_Position;
	const float size = vSize[0];

	gColor = vColor[0];

	gl_Position = projectionMatrix * (position + vec4(-size, -size, 0, 0));
	gTexCoord = vec2(0, 0);
	EmitVertex();

	gl_Position = projectionMatrix * (position + vec4(-size, size, 0, 0));
	gTexCoord = vec2(0, 1);
	EmitVertex();

	gl_Position = projectionMatrix * (position + vec4(size, -size, 0, 0));
	gTexCoord = vec2(1, 0);
	EmitVertex();

	gl_Position = projectionMatrix * (position + vec4(size, size, 0, 0));
	gTexCoord = vec2(1, 1);
	EmitVertex();

	EndPrimitive();
}
