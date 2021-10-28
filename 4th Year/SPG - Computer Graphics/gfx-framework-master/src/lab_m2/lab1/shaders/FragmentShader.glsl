#version 330

// Input
in vec2 texture_coord2;

// Uniform properties
uniform sampler2D texture_1;

// Output
out vec4 out_color;


void main()
{
    // TODO(student): Apply the texture
    out_color = texture(texture_1, texture_coord2);

    // TODO(student): Discard when alpha component < 0.75
    if (out_color.a < 0.5f) {
        discard;
    }

    //out_color = vec4(0.419, 0.584, 0.250, 0);
}
