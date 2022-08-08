#version 430

layout( location = 0 ) in vec3 in_Pos;
layout( location = 1 ) in vec3 in_Normal;
layout( location = 2 ) in vec2 in_TexCoord;
layout( location = 3 ) in vec3 in_Tangent;

out VS_OUT {
	vec3 FragmentPos;
	vec3 View;
	vec2 TexCoord;
	mat3 TBN;
	float Visibility;
} fs;

struct VertUniforms {
	mat4 Projection;
	mat4 View;
	mat4 Model;
	vec3 ViewPosition;
	bool Fog;
};

uniform VertUniforms vu;

const float density = 0.05;
const float gradient = 2.5;

void main() {
	vec4 vertPos = vu.Model * vec4(in_Pos, 1.0);
	vec4 relativeToCamera = vu.View * vertPos;
	gl_Position = vu.Projection * relativeToCamera;

	vec3 normal = normalize( ( vu.Model * vec4( in_Normal, 0.0 ) ).xyz );
	vec3 tangent = normalize( ( vu.Model * vec4( in_Tangent, 0.0 ) ).xyz );

	tangent = normalize( tangent - dot( tangent, normal ) * normal );

	fs.TBN = mat3( tangent, cross( normal, tangent ), normal );
	
	fs.FragmentPos = vertPos.xyz;
	fs.TexCoord = in_TexCoord;
	fs.View = normalize( vu.ViewPosition - vertPos.xyz );

	fs.Visibility = 1.0f;
	if( vu.Fog ){
		float dist = length(relativeToCamera.xyz);
		fs.Visibility = clamp(exp(-pow(dist*density, gradient)), 0.0, 1.0);
	}
}