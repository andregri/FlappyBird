#version 330 core

in vec4 v_Color;
in vec2 v_TexCoord;

layout (location = 0) out vec4 o_Color;

uniform sampler2D o_Texture;

void main()
{
	o_Color = texture(o_Texture, v_TexCoord) + v_Color;
}