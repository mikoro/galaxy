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

uniform int count;
uniform float minGravityDist;
uniform float gravityCoeff;
uniform vec2 mousePosition;
uniform float mouseMass;

void main()
{
	uint gid = gl_GlobalInvocationID.x;

	vec2 p1 = stars[gid].position.xy;
	vec2 s1 = stars[gid].size.xy;
	float m1 = s1.x * s1.y;

	vec2 f = vec2(0.0f);

	for (int i = 0; i < count; ++i)
	{
		vec2 p2 = stars[i].position.xy;
		vec2 s2 = stars[i].size.xy;
		float m2 = s2.x * s2.y;
		vec2 dir = p2 - p1;
		float r2 = dir.x * dir.x + dir.y * dir.y;

		if (r2 > minGravityDist)
			f += (gravityCoeff * (m1 * m2) / r2) * normalize(dir);
	}

	vec2 dir = mousePosition - p1;
	float r2 = dir.x * dir.x + dir.y * dir.y;

	if (r2 > minGravityDist)
		f += (gravityCoeff * (m1 * mouseMass) / r2) * normalize(dir);

	stars[gid].force = vec4(f, 0.0f, 0.0f);
}
