#version 330

in vec2 BG_tc;
in vec2 Cursor_tc;

out vec4 fragmentColor;

uniform sampler2D u_BG;
uniform sampler2D u_Cursor;

void main(){
	fragmentColor = texture(u_BG, BG_tc);

	if(Cursor_tc.x <= 1.0 && Cursor_tc.x >= 0.0 && Cursor_tc.y <= 1.0 && Cursor_tc.y >= 0.0){
		vec4 cursor = texture(u_Cursor, Cursor_tc);
		
		if(cursor.a > 0.9999999) fragmentColor = cursor;
	} 
}
