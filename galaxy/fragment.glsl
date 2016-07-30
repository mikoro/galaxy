#version 450 core

in vec2 gTexCoord;
in vec4 gColor;
out vec4 fColor;

void main()
{
	float d = distance(gTexCoord, vec2(0.5f, 0.5f));
	fColor = gColor;
	fColor.a *= 1.0f - 2.0f * d;
}
