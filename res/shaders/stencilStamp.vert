#version 330

layout(location=0) in vec3 in_Pos;

uniform mat4 u_PVM;

void main() {
	gl_Position = u_PVM * vec4(in_Pos,1.0);
}