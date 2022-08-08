#version 330

in vec2 TexCoord;

out vec4 fragmentColor;

uniform sampler2D u_Portal;

void main(){
	fragmentColor = texture(u_Portal, TexCoord);
}
