#version 330

// Input and output topologies
// TODO(student): First, generate a curve (via line strip),
// then a rotation/translation surface (via triangle strip)
layout(lines) in;
// layout(line_strip, max_vertices = 256) out;
layout(triangle_strip, max_vertices = 256) out;

// Uniform properties
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 control_p0, control_p1, control_p2, control_p3;
uniform int no_of_instances;
// TODO(student): Declare any other uniforms here
uniform int no_of_generated_points;

// Input
in int instance[2];

vec3 rotateY(vec3 point, float u)
{
    float x = point.x * cos(u) - point.z *sin(u);
    float z = point.x * sin(u) + point.z *cos(u);
    return vec3(x, point.y, z);
}


vec3 translateX(vec3 point, float t)
{
    return vec3(point.x + t, point.y, point.z);
}


// This function computes B(t) with 4 control points. For a visual example,
// see [1]. For an interactive Javascript example with the exact points in
// this code, see [2].
//
// [1] https://www.desmos.com/calculator/cahqdxeshd
// [2] https://jsfiddle.net/6yuv9htf/
vec3 bezier(float t)
{
    return  control_p0 * pow((1 - t), 3) +
            control_p1 * 3 * t * pow((1 - t), 2) +
            control_p2 * 3 * pow(t, 2) * (1 - t) +
            control_p3 * pow(t, 3);
}

// TODO(student): If you want to take things a step further, try drawing a
// Hermite spline. Hint: you can repurpose two of the control points. For a
// visual example, see [1]. For an interactive Javascript example with the
// exact points in this code, see [2].
// 
// Unlike the Javascript function, you MUST NOT call the Bezier function.
// There is another way to draw a Hermite spline, all you need is to find
// the formula.
//
// [1] https://www.desmos.com/calculator/5knm5tkr8m
// [2] https://jsfiddle.net/6yuv9htf/

void main()
{
    const int SURFACE_TYPE_ROTATION     = 0;
    const int SURFACE_TYPE_TRANSLATION  = 1;

    // You can change the value of SURFACE_TYPE to experiment
    // with different transformation types.
    const int SURFACE_TYPE = SURFACE_TYPE_TRANSLATION;

    if (instance[0] < no_of_instances)
    {
        // TODO(student): Rather than emitting vertices for the control
        // points, you must emit vertices that approximate the curve itself.
        /*
        gl_Position = Projection * View * vec4(control_p0, 1);   EmitVertex();
        gl_Position = Projection * View * vec4(control_p1, 1);   EmitVertex();
        gl_Position = Projection * View * vec4(control_p2, 1);   EmitVertex();
        gl_Position = Projection * View * vec4(control_p3, 1);   EmitVertex();
        EndPrimitive();
        */

        // CURBA BEZIER simpla
        /*
        float i = 0.f;
        float accuracy = 1.f / no_of_generated_points;

        gl_Position = Projection * View * vec4(control_p0, 1);
        EmitVertex();

        for(; i <= 1.f; i += accuracy) {
            gl_Position = Projection * View * vec4(bezier(i), 1);
            EmitVertex();
        }

        gl_Position = Projection * View * vec4(control_p3, 1);
        EmitVertex();

        EndPrimitive();
        */
        
        // MESH
        int j;
        float acc = 1.f / no_of_generated_points;
        for (j = 0; j < no_of_instances; ++j) {
            vec3 leftUpper = translateX(bezier(0.f), j);
            vec3 leftLower = translateX(bezier(acc), j);
            float i = 2 * acc;

            for (; i <= 1.f; i += acc) {
                gl_Position = Projection * View * vec4(leftUpper, 1);
                EmitVertex();

                gl_Position = Projection * View * vec4(translateX(leftUpper, 1.f), 1);
                EmitVertex();

                gl_Position = Projection * View * vec4(leftLower, 1);
                EmitVertex();

                EndPrimitive();

                gl_Position = Projection * View * vec4(leftLower, 1);
                EmitVertex();

                gl_Position = Projection * View * vec4(translateX(leftUpper, 1.f), 1);
                EmitVertex();

                gl_Position = Projection * View * vec4(translateX(leftLower, 1.f), 1);
                EmitVertex();

                EndPrimitive();

                leftUpper = leftLower;
                leftLower = translateX(bezier(i), j);
            }
        }
    }
}
