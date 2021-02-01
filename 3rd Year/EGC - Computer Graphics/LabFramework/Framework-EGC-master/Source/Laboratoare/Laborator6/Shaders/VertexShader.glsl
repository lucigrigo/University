#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texture;
layout(location = 3) in vec3 color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

// aici am interschimbat pipe-urile 1 si 3
out vec3 fragment_position;
out vec3 fragment_color;
out vec2 fragment_texture;
out vec3 fragment_normal;

void main()
{
	fragment_position = position;
	fragment_normal = normal;
	fragment_texture = texture;
	fragment_color = color;

	gl_Position = Projection * View * Model * vec4(position, 1.0);
}
