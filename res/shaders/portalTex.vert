#version 330

layout(location=0) in vec3 in_Pos;
layout(location=2) in vec2 in_TexCoords;

uniform mat4 u_Model;
uniform mat4 u_PV;
uniform int u_Frame;

out vec2 TexCoord;

const int frames = 10;

const float texStep = 0.1;

void main() {
	TexCoord.x = in_TexCoords.x / 10 + u_Frame * texStep;
	TexCoord.y = in_TexCoords.y;

	gl_Position = u_PV * u_Model * vec4(in_Pos, 1.0f);
}
