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

varying float noise;

out vec3 fragment_position;
out vec3 fragment_normal;
out vec3 fragment_color;
out vec2 fragment_texture;
out vec3 sec_color;

const float amplitude = 0.25;
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
		float x = 0.15 * (1 + cos(10 * position.x * time)) / 2;
        float y = 0.15 * (1 + cos(10 * position.y * time)) / 2;
        float z = 0.15 * (1 + cos(10 * position.z * time)) / 2;

		gl_Position = Projection * View * Model * vec4(position.x + x, position.y + y, position.z + z, 1.0);
	} else {
		gl_Position = Projection * View * Model * vec4(position, 1);
	}
}