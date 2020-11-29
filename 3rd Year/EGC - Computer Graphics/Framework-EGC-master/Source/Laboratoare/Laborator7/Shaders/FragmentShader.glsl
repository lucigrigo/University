#version 330

layout(location = 0) out vec4 out_color;

// Get color value from vertex shader
in vec3 color;

void main()
{
	// Write pixel out color
	out_color = vec4(color, 1);
}