#shader vertex
#version 430 core

in vec2 position; // the index (0), a vec4 and not a vec2 because position is vec4
in vec2 texCoord;

uniform mat4 u_mvp; // Model View projection matrix
uniform float u_is_texture;

out vec2 v_texCoord;
out float v_is_texture;

void main() {
	if (u_is_texture > 0.5) {
		v_texCoord = texCoord;
	}
	gl_Position = u_mvp * vec4(position, 0.0, 1.0);
};

#shader fragment
#version 430 core
out vec4 color;

in vec2 v_texCoord;

uniform sampler2D u_texture;
uniform vec4 u_color;
uniform float u_is_texture;

void main() {
	if (u_is_texture > 0.5) {
		vec4 texColor = texture(u_texture, v_texCoord);
		color = texColor; // rgba [0,1] instead of [0,255]
	}
	else {
		color = vec4(1.0, 0.0, 0.0, 1.0);
	}
};