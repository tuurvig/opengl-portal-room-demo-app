#version 430

struct Texture {
	sampler2D source;
	bool enabled;
};

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
    float shininess;
};

struct PointLight {
	vec3 position;
	vec3 diffuse;
	vec3 specular;
	vec3 ambient;
	vec2 attenuation;
	float intensity;
};

struct SpotLight {
	vec3 position;
	vec3 direction;
	vec3 diffuse;
	vec3 specular;
	vec2 cutOff;
};

struct DirectionalLight{
	vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	float intensity;
};

struct FragUniforms{
	Material material;
	Texture t_Diffuse;
	Texture t_Specular;
	Texture t_Normal;
	Texture t_Roughness;
	Texture t_Occlusion;
	Texture t_Opacity;
	PointLight point[10];
	SpotLight spot[10];
	DirectionalLight sun;
	int pointLights;
	int spotLights;
	samplerCube cubeMap;
	vec3 skyColor;
};

in VS_OUT {
	vec3 FragmentPos;
	vec3 View;
	vec2 TexCoord;
	mat3 TBN;
	float Visibility;
} fs;

uniform FragUniforms fu;

out vec4 fragmentColor;

const vec3 gamma = vec3(2.2);
const vec3 gammaInv = vec3(0.454545454545454545454545454545454545);

DirectionalLight Sun;

vec3 GetNormal(){
	if( fu.t_Normal.enabled ){
		vec3 normal = texture( fu.t_Normal.source, fs.TexCoord ).rgb * 2.0 - 1.0;
		return normalize( fs.TBN * normal );
	}

	return normalize( fs.TBN[2] );
}

vec4 ProcessLight(){
	vec3 fragmentPosition = fs.FragmentPos;
	vec3 specular = fu.t_Specular.enabled ? texture( fu.t_Specular.source, fs.TexCoord ).rgb : fu.material.specular;
	vec3 ambient = fu.material.ambient;
	vec3 diffuse = fu.material.diffuse;
	float shininess = fu.material.shininess;

	vec3 normal = GetNormal();

	vec3 view = normalize( fs.View );

	if( fu.t_Diffuse.enabled ){
		diffuse = pow(texture(fu.t_Diffuse.source, fs.TexCoord).rgb, gamma); 
		ambient = diffuse;
	}

	if( fu.t_Roughness.enabled ){
		float rough = texture( fu.t_Roughness.source, fs.TexCoord ).g;
		float k = 1.999 / ( rough * rough );
		shininess = k;
		specular *= k;
	}

	vec3 color = vec3(0.0);

	// Calculating point lights
	for( int i = 0; i < fu.pointLights; ++i){
		const PointLight point = fu.point[ i ];

		vec3 light = vec3(0.0);

		const vec3 toLight = point.position - fragmentPosition;
		const float dist = length( toLight );
		const float attenuation = 1.0 / ( 1.0 + point.attenuation.x * dist + point.attenuation.y * dist * dist );

		const vec3 L = toLight / dist; // normalize
		const vec3 R = reflect( -L, normal );

		light += ambient * point.ambient;
		light += diffuse * max( 0.0, dot( normal, L ) ) * point.intensity;
		light += specular * point.specular * pow( max( 0.0, dot( R, view ) ), shininess );
		light *= attenuation * point.diffuse;
		//light *= attenuation;

		color += pow(light, gammaInv);
	}

	for( int i = 0; i < fu.spotLights; ++i ){
		SpotLight spot = fu.spot[ i ];

		vec3 light = vec3(0.0);
		vec3 toLight = spot.position - fragmentPosition;
		float dist = length( toLight );

		vec3 L = toLight / dist;
		float theta = dot(L, normalize(-spot.direction));

		if( theta > spot.cutOff.y ){
			vec3 R = reflect( -L, normal );
			float transition = spot.cutOff.x - spot.cutOff.y;
			float intensity = smoothstep( 0.0, 1.0, ( theta - spot.cutOff.y ) / transition );

			light += ambient * 0.01;
			light += intensity * diffuse * max( 0.0, dot( normal, L ) );
			light += specular * spot.specular * pow( max( 0.0, dot( R, view ) ), shininess );
			light *= spot.diffuse;

			color += pow(light, gammaInv);
		}
	}

	// directional light calculation

	DirectionalLight direct = Sun;
	vec3 light = vec3(0.0);
	vec3 L = normalize(-direct.direction);
	vec3 R = reflect(-L, normal);

	light += ambient * direct.ambient;
	light += diffuse * max( 0.0, dot( normal, L ) ) * direct.intensity;
	light += specular * direct.specular * pow( max( 0.0, dot( R, view ) ), shininess );
	light *= direct.diffuse;

	color += pow(light, gammaInv);

	R = reflect(-view, normal);
	float RdotV = max( 0.0, dot( -R, view ) );
	vec3 cubeColor = pow(texture(fu.cubeMap, R).rgb, gamma);
	float shine = pow( RdotV , shininess );
	vec3 mixEnv = specular * shine;
	mixEnv += ambient * 0.15;
	mixEnv *= cubeColor;
	mixEnv = pow( mixEnv, gammaInv );

	vec4 finalColor = vec4(mix(color, mixEnv, 0.4), 1.0);

	if( fu.t_Occlusion.enabled ) finalColor.rgb *= texture( fu.t_Occlusion.source, fs.TexCoord ).rgb;
	if( fu.t_Opacity.enabled ) finalColor.a *= texture( fu.t_Opacity.source, fs.TexCoord ).r;

	return finalColor;
}

void main(){
	Sun.direction = vec3( 0.0, 0.0, -1.0);
	Sun.ambient = vec3(0.2);
	Sun.diffuse = vec3(0.9, 0.8, 0.5);
	Sun.specular = vec3(0.2);
	Sun.intensity = 1.0;

	fragmentColor += ProcessLight();

	fragmentColor = mix(vec4(fu.skyColor,1.0), fragmentColor, fs.Visibility);
}
