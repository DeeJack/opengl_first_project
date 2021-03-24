#shader vertex
#version 330 core

layout(location = 0) in vec4 position; // the index (0), a vec4 and not a vec2 because position is vec4
layout(location = 1) in vec3 color;

uniform mat4 u_mvp; // Model View projection matrix

out vec3 v_color;

void main() {
	gl_Position = u_mvp * position;
	v_color = color;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color; // 

in vec3 v_color;

//uniform vec4 u_color; // Use a variable from the cpu side

void main() {
	//vec4 texColor = texture(u_texture, v_texCoord);
	//color = texColor; // rgba [0,1] instead of [0,255]
	color = vec4(v_color, 1.0);
};