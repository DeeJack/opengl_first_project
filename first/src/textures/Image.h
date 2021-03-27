#pragma once
#include <functional>

class Image
{
private:
	unsigned char* _local_buffer = nullptr;
	int _width = 0;
	int _height = 0;
	int _bpp = 0; // Bits per pixel
public:
	Image() = default;
	
	~Image();

	unsigned char* load_image(const char* path);

	/**
	 * \brief 
	 * \param path The path of the image
	 * \param function A callback function that will be called with the pointer to the buffer
	 */
	void load_image_async(const char* path, std::function<void()> function);


	unsigned char* local_buffer() const
	{
		return _local_buffer;
	}

	int width() const
	{
		return _width;
	}

	int height() const
	{
		return _height;
	}
};
