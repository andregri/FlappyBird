#version 330 core

layout (location = 0) out vec4 color;

in DATA
{
	vec2 tc;
} fs_in;

uniform sampler2D tex;
uniform int u_top;

void main()
{
	vec2 new_tc = fs_in.tc;
	if (u_top == 1)
		new_tc.y = 1.0 - fs_in.tc.y;

	color = texture(tex, new_tc);
	if (color.w < 1.0)
		discard;
}