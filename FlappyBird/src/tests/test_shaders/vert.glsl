#version 330 core

layout (location = 0) in vec4 a_Position;
layout (location = 1) in vec4 a_Color;

out vec4 color;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * a_Position;
	color = a_Color;
}