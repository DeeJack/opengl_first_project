#pragma once
#include <functional>
#include <string>

class Texture
{
private:
	unsigned int _renderer_id = 0;
	int _width = 0;
	int _height = 0;

	void load_texture(const unsigned char* const buffer);
public:
	Texture();
	explicit Texture(const char* path);
	~Texture();

	// TODO: load textures async
	void load(const char* path);
	void load_async(const char* path, std::function<void()> callback);
	void bind(const unsigned int slot = 0) const;
	static void unbind();

	inline int get_width() const { return _width; }
	inline int get_height() const { return _height; }
};