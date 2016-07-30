#version 450 core

struct Star
{
	vec3 position;
	float size;
	vec4 color;
};

layout (std140, binding = 0) buffer StarBuffer
{
	Star stars[];
};

layout(local_size_x = 128) in;

void main()
{
	uint id = gl_GlobalInvocationID.x;
	float size = stars[id].size;

	stars[id].size += 0.01f;
}
