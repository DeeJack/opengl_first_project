#shader vertex
#version 330 core

layout(location = 0) in vec4 position; // the index (0), a vec4 and not a vec2 because position is vec4
layout(location = 1) in vec3 color;
//layout(location = 1) in vec2 textCoord;

uniform mat4 u_mvp; // Model View projection matrix

//out vec2 v_texCoord;
out vec3 v_color;

void main() {
	gl_Position = u_mvp * position;
	//v_texCoord = textCoord;
	v_color = color;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color; // 

//in vec2 v_texCoord;
in vec3 v_color;

//uniform vec4 u_color; // Use a variable from the cpu side
uniform sampler2D u_texture;

void main() {
	//vec4 texColor = texture(u_texture, v_texCoord);
	color = vec4(v_color, 1.0); // rgba [0,1] instead of [0,255]
	//color = vec4(v_color, 1.0);
};