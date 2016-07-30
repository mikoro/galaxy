#version 450 core

#define STAR_COUNT 32768
#define COMPUTE_GROUP_SIZE 512

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

void main()
{
	uint gid = gl_GlobalInvocationID.x;

	vec2 p1 = stars[gid].position.xy;
	vec2 s1 = stars[gid].size.xy;
	float m1 = s1.x * s1.y;

	vec2 f = vec2(0.0f);

	for (int i = 0; i < STAR_COUNT; ++i)
	{
		vec2 p2 = stars[i].position.xy;
		vec2 s2 = stars[i].size.xy;
		float m2 = s2.x * s2.y;
		vec2 dir = p2 - p1;
		float r2 = dir.x * dir.x + dir.y * dir.y;

		if (r2 > 1.0f)
			f += (0.1f * (m1 * m2) / r2) * normalize(dir);
	}

	stars[gid].force = vec4(f, 0.0f, 0.0f);
}
