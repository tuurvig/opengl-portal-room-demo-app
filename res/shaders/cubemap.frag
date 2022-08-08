#version 330

in vec3 Look;

out vec4 fragmentColor;

uniform samplerCube u_Cubemap;

void main(){
	fragmentColor = texture(u_Cubemap, Look);
}
