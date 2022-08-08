#version 330

layout(location=0) in vec3 in_Pos;
layout(location=2) in vec2 in_TexCoords;

uniform mat3 u_CursorMatrix;

out vec2 BG_tc;
out vec2 Cursor_tc;

void main() {
	BG_tc = in_TexCoords;
	
	vec2 cursor = in_TexCoords;
	cursor.y = 1 - cursor.y;

	Cursor_tc = (u_CursorMatrix * vec3(cursor, 1.0)).xy;

	vec4 fragPos = vec4(in_Pos, 1.0f);
	gl_Position = fragPos;
}
