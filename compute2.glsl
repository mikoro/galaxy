#version 430 core

#define COMPUTE_GROUP_SIZE 128

struct Star
{
	vec4 position;
	vec4 velocity;
	vec4 force;
	vec4 size;
	vec4 color;
};

layout (std140, binding = 0) buffer StarBuffer
{
	Star stars[];
};

layout(local_size_x = COMPUTE_GROUP_SIZE) in;

uniform float dt;

void main()
{
	const uint gid = gl_GlobalInvocationID.x;

	vec2 p = stars[gid].position.xy;
	vec2 v = stars[gid].velocity.xy;
	vec2 f = stars[gid].force.xy;
	vec2 s = stars[gid].size.xy;

	float m = s.x * s.y;
	float v2 = v.x * v.x + v.y * v.y;
	float drag = 0.001f * v2;

	v += (f / m) * dt;
	v += -normalize(v) * drag * dt;
	p += v * dt;

	stars[gid].position = vec4(p, 0.0f, 1.0f);
	stars[gid].velocity = vec4(v, 0.0f, 0.0f);
}
