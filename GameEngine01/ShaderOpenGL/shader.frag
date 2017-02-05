#version 330 core

in DATA {
	vec4 pos;
	vec4 color;
} fs_in;

layout (location = 0) out vec4 outcolor;

uniform vec4 color;
uniform vec2 light_pos;

void main()
{
	float intensity = 1.0 / length(fs_in.pos.xy - light_pos);
    //outcolor = ucolor * intensity;
	outcolor = fs_in.color * intensity;
}