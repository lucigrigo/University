#version 330

// TODO: get color value from vertex shader
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 light_position;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

uniform vec3 object_color;
uniform int is_using_spotlight;

layout(location = 0) out vec4 out_color;

void main()
{
	vec3 N = normalize(world_normal);
	vec3 L = normalize(light_position - world_position);
	vec3 V = normalize(eye_position - world_position);
	vec3 H = normalize(L + V);
	vec3 R = normalize(reflect(L, world_normal));

	// TODO: define ambient light component
	float ambient_light = 0.25;

	// TODO: compute diffuse light component
	float diffuse_light = material_kd * max(dot(normalize(N), L), 0.f);

	// TODO: compute specular light component
	float specular_light = 0.f;

	if (diffuse_light > 0)
	{
		specular_light = material_ks * pow(max(dot(N, H), 0), material_shininess);
	}

	// TODO: compute light
	float light = 0.f;

	if(is_using_spotlight == 1)
	{
		float cut_off_radians = radians(30.f);
		float spot_light = dot(-L, light_direction);
		float spot_light_lim = cos(cut_off_radians);

		if(spot_light > spot_light_lim)
		{
			float att = (spot_light - spot_light_lim) / (1.f - spot_light_lim);
			float light_att = att * att;
			light = ambient_light + light_att * (diffuse_light + specular_light);
		}
		else
		{
			light = ambient_light;
		}
	} 
	else
	{
		float d = distance(light_position, world_position);
		float att_fact = 1.f / max(d * d, 1.f);
		light = ambient_light + att_fact * (diffuse_light + specular_light);
	}

	// TODO: write pixel out color
	vec3 col = object_color * light;
	out_color = vec4(col, 1.f);
}