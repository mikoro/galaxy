#version 450 core

in vec3 colorVarying;
out vec3 color;

void main()
{
	color = colorVarying;
}
