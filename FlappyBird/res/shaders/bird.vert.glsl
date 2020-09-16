#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 tex_coord;

out DATA
{
	vec2 tc;
} vs_out;

uniform mat4 u_proj;
uniform mat4 u_view = mat4(1.0f);
uniform mat4 u_model = mat4(1.0f);

void main()
{
	gl_Position = u_proj * u_view * u_model * position;
	vs_out.tc = tex_coord;
}