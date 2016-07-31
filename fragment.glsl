#version 450 core

in vec2 gTexCoord;
in vec4 gColor;
out vec4 fColor;

void main()
{
	float d = distance(gTexCoord, vec2(0.5f, 0.5f));
	vec4 color = pow(gColor, vec4(1.0f/2.2f));
	color.a = gColor.a * pow((1.0f - (2.0f * d)), 0.5f);
	fColor = clamp(color, 0.0f, 1.0f);
}
