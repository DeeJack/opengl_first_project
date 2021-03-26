#include <GLEW/glew.h>
#include "VertexBuffer.h"
#include "../log.h"
#include <string>

VertexBuffer::VertexBuffer(const void* data, const unsigned int size, const unsigned int vertices_count)
	: _vertices_count(vertices_count)
{
	glGenBuffers(1, &_renderer_id); // Number of buffers, address of the buffers' name
	set_data(data, size);
}

VertexBuffer::~VertexBuffer()
{
	log("Destroyed VertexBuffer (" + std::to_string(_renderer_id) + ")");
	glDeleteBuffers(1, &_renderer_id);
}

void VertexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, _renderer_id); // Bind the buffer to a buffer type
}

void VertexBuffer::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind
}

unsigned int VertexBuffer::vertices_count() const
{
	return _vertices_count;
}

void VertexBuffer::set_data(const void* data, const unsigned int size) const
{
	bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
