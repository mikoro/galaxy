#version 450 core

in vec2 gTexCoord;
in vec3 gColor;
out vec4 fColor;

void main()
{
	float d = distance(gTexCoord, vec2(0.5f, 0.5f));
	fColor = vec4(gColor.rgb, 1.0f - 2.0f * d);
}
