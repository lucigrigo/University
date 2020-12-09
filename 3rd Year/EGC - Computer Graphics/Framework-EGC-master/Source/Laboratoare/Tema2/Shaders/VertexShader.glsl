#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texture;
layout(location = 3) in vec3 color;

uniform vec3 object_color;
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform int defform;
uniform float time;

out vec3 fragment_position;
out vec3 fragment_normal;
out vec3 fragment_color;
out vec2 fragment_texture;
out vec3 sec_color;

const float amplitude = 0.5;
const float frequency = 10;
const float PI = 3.14159;

void main() 
{
	fragment_position = position;
	fragment_normal = normal;
	fragment_texture = texture;
	fragment_color = color;
	sec_color = object_color;

	if(defform == 1) {
		float distance = length(position);
		float y = amplitude * sin(-PI * distance * frequency + time);

		//y = 0.5 * sin(PI * distance * frequency + time);
		//x = 0.5 * sin(PI * distance * frequency + time);

		gl_Position = Projection * View * Model * vec4(position.x, y, position.z, 1.0);
	} else {
		gl_Position = Projection * View * Model * vec4(position, 1);
	}
}