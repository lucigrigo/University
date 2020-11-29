#version 330

// TODO: get color value from vertex shader
layout(location = 0) out vec4 out_color;

in vec3 in_color;

void main()
{
	// TODO: write pixel out color
	out_color = vec4(in_color, 1);
}