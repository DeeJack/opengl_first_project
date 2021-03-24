#pragma once
#include <vector>
#include "../../log.h"

struct BufferLayoutElement
{
	unsigned int type; // The GLenum type
	unsigned int count; // The count of elements of the vertex
	unsigned char normalized; // Whether the element needs to be normalized

	static unsigned int size_of_type(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT: return sizeof(GLfloat);
		case GL_UNSIGNED_INT: return sizeof(GLuint);
		case GL_UNSIGNED_BYTE: return sizeof(GLubyte);
		}
		ASSERT(false);
		return 0;
	}
};

class BufferLayout
{
private:
	std::vector<BufferLayoutElement> _elements;
	unsigned int _stride = 0; // The 
public:
	BufferLayout() : _stride(0) {}

	template<typename T>
	void push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void push<float>(unsigned int count)
	{
		_elements.push_back({ GL_FLOAT, count, GL_FALSE });
		_stride += count * BufferLayoutElement::size_of_type(GL_FLOAT);
	}

	template<>
	void push<unsigned int>(unsigned int count)
	{
		_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		_stride += count * BufferLayoutElement::size_of_type(GL_UNSIGNED_INT);
	}

	template<>
	void push<unsigned char>(unsigned int count)
	{
		_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		_stride += count * BufferLayoutElement::size_of_type(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<BufferLayoutElement>& get_elements() const { return _elements;  }

	inline unsigned int get_stride() const { return _stride;  }
};