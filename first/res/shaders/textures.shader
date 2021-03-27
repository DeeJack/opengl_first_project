#shader vertex
#version 330 core

in vec2 position; // the index (0), a vec4 and not a vec2 because position is vec4
in vec2 texCoord;

uniform mat4 u_mvp; // Model View projection matrix

out vec2 v_texCoord;

void main() {
	gl_Position = u_mvp * vec4(position, 0.0, 1.0);
	v_texCoord = texCoord;
};

#shader fragment
#version 330 core
// layout(location = 0) 
out vec4 color;

in vec2 v_texCoord;

uniform sampler2D u_texture;	

void main() {
	vec4 texColor = texture(u_texture, v_texCoord);
	color = texColor; // rgba [0,1] instead of [0,255]
};