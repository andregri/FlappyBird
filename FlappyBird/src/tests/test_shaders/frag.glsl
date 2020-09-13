#version 330 core

layout (location = 0) out vec4 o_Color;

in vec4 color;

void main()
{
	o_Color = color;
}