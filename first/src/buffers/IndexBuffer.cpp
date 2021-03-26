#include "IndexBuffer.h"

#include "../log.h"
#include <string>

IndexBuffer::IndexBuffer(const unsigned int* data, const unsigned int count)
	: _indices_count(count)
{
	glGenBuffers(1, &_renderer_id); // Number of buffers, address of the buffers' name
	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	log("Destroyed IndexBuffer (" + std::to_string(_renderer_id) + ")");
	glDeleteBuffers(1, &_renderer_id);
}

void IndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _renderer_id); // Bind the buffer to a buffer type
}

void IndexBuffer::unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Bind the buffer to a buffer type
}

unsigned IndexBuffer::get_count() const
{
	return _indices_count;
}
