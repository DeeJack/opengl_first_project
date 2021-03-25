#pragma once
#include <string>

class Texture
{
private:
	unsigned int _renderer_id = 0;
	std::string _file_path;
	unsigned char* _local_buffer = nullptr;
	int _width = 0, _height = 0, _bpp = 0; // Bits per pixel
public:
	Texture();
	Texture(const std::string& path);
	~Texture();

	// TODO: load textures async
	void load(const std::string& path);
	void bind(unsigned int slot = 0) const;
	void unbind() const;

	inline int get_width() const { return _width; }
	inline int get_height() const { return _height; }

};