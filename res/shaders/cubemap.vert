#version 330

layout(location=0) in vec3 in_Pos;

uniform mat4 u_PV;

out vec3 Look;

void main() {
	Look = in_Pos;
	vec4 fragPos = u_PV * vec4(in_Pos, 1.0f);
	gl_Position = fragPos.xyww;
}