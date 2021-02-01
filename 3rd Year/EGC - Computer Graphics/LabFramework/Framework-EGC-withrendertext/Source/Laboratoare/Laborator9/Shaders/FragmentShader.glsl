#version 330
 
uniform sampler2D texture_1;
uniform sampler2D texture_2;
uniform bool mixtex;

in vec2 texcoord;

layout(location = 0) out vec4 out_color;

void main()
{
	// TODO : calculate the out_color using the texture2D() function
	vec4 col1 = texture2D(texture_1, texcoord);
	vec4 col2 = texture2D(texture_2, texcoord);

	if(mixtex == true) {
		out_color = mix(col1, col2, 0.6f);
	} else {
		out_color = col1;
	}

	if(out_color.a < 0.5f) {
		discard;
	}
}