#include "GLEW/glew.h"
#include "Texture.h"
#include "stb_image/stb_image.h"
#include <stdexcept>
#include "../log.h"

Texture::Texture() = default;

Texture::Texture(const std::string & path)
	: _file_path(path)
{
	load(path);
}

void Texture::load(const std::string& path)
{
	_file_path = path;
	stbi_set_flip_vertically_on_load(1); // OpenGL expect the texture to start from the bottom left
	int _bpp = 0; // Bits per pixel
	_local_buffer = stbi_load(path.c_str(), &_width, &_height, &_bpp, 4); // 4 because R, G, B, A

	glGenTextures(1, &_renderer_id);
	bind(0);

	// GL_TEXTURE_MIN_FILTER -> minification, scale down the texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// Mag -> magnification, if the area is bigger
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// The wrap (???)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// internal format: how openGL will store the data, format: how you provide the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _local_buffer);
	unbind();

	if (_local_buffer)
		stbi_image_free(_local_buffer);
}

Texture::~Texture()
{
	unbind();
	glDeleteTextures(1, &_renderer_id);
	log("Destroyed Texture (" + std::to_string(_renderer_id) + ")");
}

void Texture::bind(unsigned int slot) const
{
	if (slot > 31)
		throw std::invalid_argument("Invalid slot: " + std::to_string(slot));
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, _renderer_id);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
