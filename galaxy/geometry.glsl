#version 450 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

uniform mat4 projectionMatrix;

in vec3 vColor[];
out vec3 gColor;

void main(void)
{
	for (int i = 0; i < gl_in.length(); ++i)
	{
		gl_Position = projectionMatrix * gl_in[i].gl_Position;
		gColor = vColor[i];
		EmitVertex();
	}

	EndPrimitive();
}
