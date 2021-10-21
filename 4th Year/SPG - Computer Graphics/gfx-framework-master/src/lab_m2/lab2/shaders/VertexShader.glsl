#version 330

// Input
in vec3 v_position;
in vec3 v_normal;
in vec2 v_texture_coord;

// Uniform properties
uniform mat4 Model;

// Output
out int instance;


void main()
{
    instance = gl_InstanceID;
    gl_Position =  Model * vec4(v_position, 1);
}
