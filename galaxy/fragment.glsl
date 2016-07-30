#version 450 core

in vec2 gTexCoord;
in vec4 gColor;
out vec4 fColor;

void main()
{
	float d = distance(gTexCoord, vec2(0.5f, 0.5f));
	fColor = gColor;

	fColor.r = pow(gColor.r, 1.0f / 2.2f);
	fColor.g = pow(gColor.g, 1.0f / 2.2f);
	fColor.b = pow(gColor.b, 1.0f / 2.2f);
	fColor.a *= 1.0f - 2.0f * d;
}
