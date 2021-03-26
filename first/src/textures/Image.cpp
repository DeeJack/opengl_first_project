#include "Image.h"

#include <thread>

#include "stb_image/stb_image.h"

Image::~Image()
{
	delete _local_buffer;
}

unsigned char* Image::load_image(const char* path)
{
	stbi_set_flip_vertically_on_load(1); // OpenGL expect the texture to start from the bottom left
	_local_buffer = stbi_load(path, &_width, &_height, &_bpp, 4); // 4 because R, G, B, A
	return _local_buffer;
}

void Image::load_image_async(const char* path, const std::function<void()> function)
{
	std::thread t([this, path, function]
	{
		load_image(path);
		function();
		//delete _thread;
	});
	t.detach();
}
