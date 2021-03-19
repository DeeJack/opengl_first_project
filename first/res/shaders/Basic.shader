#shader vertex
#version 330 core

layout(location = 0) in vec4 position; // the index (0), a vec4 and not a vec2 because position is vec4
layout(location = 1) in vec2 texCoord;

uniform mat4 u_mvp; // Model View projection matrix

out vec2 v_texCoord;

void main() {
	gl_Position = u_mvp * position;
	v_texCoord = texCoord;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color; // 

in vec2 v_texCoord;

uniform vec4 u_Color; // Use a variable from the cpu side
uniform sampler2D u_texture;

void main() {
	vec4 texColor = texture(u_texture, v_texCoord);
	color = texColor; // rgba [0,1] instead of [0,255]
};