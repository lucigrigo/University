#version 330

uniform sampler2D texture;

in vec3 fragment_position;
in vec3 fragment_normal;
in vec3 fragment_color;
in vec2 fragment_texture;
in vec3 sec_color;
flat in int frag_has_texture;

layout(location = 0) out vec4 out_color;
layout(location = 1) out vec4 out_normal;
layout(location = 2) out vec3 out_texture;

void main()
{
	if(sec_color != vec3(0.f, 0.f, 0.f)) {
		vec4 color = texture2D(texture, fragment_texture);
		out_color = mix(color, vec4(sec_color, 1), 0.75f);
	} else {
		out_color = texture2D(texture, fragment_texture);
	}
}