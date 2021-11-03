#version 430

// Input
layout(location = 0) in vec3 world_position;
layout(location = 1) in vec3 world_normal;

// Uniform properties
uniform sampler2D texture_1;
uniform samplerCube texture_cubemap;

uniform vec3 camera_position;

// Output
layout(location = 0) out vec4 out_color;


vec3 myReflect()
{
    // TODO(student): Compute the reflection color value
    vec3 razaIncidenta = normalize(world_position - camera_position);
    return reflect(razaIncidenta, world_normal);
}


vec3 myRefract(float refractive_index)
{
    // TODO(student): Compute the refraction color value
    vec3 razaIncidenta = normalize(world_position - camera_position);
    //return refract(razaIncidenta, world_normal, refractive_index);
    return refract(razaIncidenta, world_normal, 1.0f); // because it looks cool :)
}


void main()
{
    const int LIGHT_PROP_REFLECTION = 0;
    const int LIGHT_PROP_REFRACTION = 1;

    // You can change the value of LIGHT_PROP to experiment
    // with different light propagation methods.
    const int LIGHT_PROP = LIGHT_PROP_REFLECTION;

    if (LIGHT_PROP == LIGHT_PROP_REFLECTION)
    {
        out_color = texture(texture_cubemap, myReflect());
    }
    else
    {
        out_color = texture(texture_cubemap, myRefract(1.0f / 1.33f));
    }
}
