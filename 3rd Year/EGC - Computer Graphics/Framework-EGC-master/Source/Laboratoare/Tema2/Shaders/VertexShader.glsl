#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texture;
layout(location = 3) in vec3 color;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 object_color;

out vec3 fragment_position;
out vec3 fragment_normal;
out vec3 fragment_color;
out vec2 fragment_texture;
out vec3 sec_color;

void main() 
{

	fragment_position = position;
	fragment_normal = normal;
	fragment_texture = texture;
	fragment_color = color;
	sec_color = object_color;

	gl_Position = Projection * View * Model * vec4(position, 1.0);
}