#shader vertex
#version 330 core

layout(location = 0) in vec4 position; // the index (0), a vec4 and not a vec2 because position is vec4

uniform mat4 u_mvp; // Model View projection matrix

void main() {
	gl_Position = u_mvp * position;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color; // 

uniform vec4 u_color; // Use a variable from the cpu side

void main() {
	//vec4 texColor = texture(u_texture, v_texCoord);
	//color = texColor; // rgba [0,1] instead of [0,255]
	color = u_color;
};