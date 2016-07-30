#version 450 core

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

uniform mat4 projectionMatrix;

in vec3 vColor[];
out vec2 gTexCoord;
out vec3 gColor;

void main(void)
{
	const vec4 position = gl_in[0].gl_Position;
	const vec3 color = vColor[0];
	const float width = 60.0f;

	gColor = color;

	gl_Position = projectionMatrix * (position + vec4(-width, -width, 0, 0));
	gTexCoord = vec2(0, 0);
	EmitVertex();

	gl_Position = projectionMatrix * (position + vec4(-width, width, 0, 0));
	gTexCoord = vec2(0, 1);
	EmitVertex();

	gl_Position = projectionMatrix * (position + vec4(width, -width, 0, 0));
	gTexCoord = vec2(1, 0);
	EmitVertex();

	gl_Position = projectionMatrix * (position + vec4(width, width, 0, 0));
	gTexCoord = vec2(1, 1);
	EmitVertex();

	EndPrimitive();
}
