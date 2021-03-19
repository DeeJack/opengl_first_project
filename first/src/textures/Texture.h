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
	Texture(const std::string& path);
	~Texture();

	void bind(unsigned int slot = 0) const;
	void unbind() const;

	inline int get_width() { return _width; }
	inline int get_height() { return _height; }

};