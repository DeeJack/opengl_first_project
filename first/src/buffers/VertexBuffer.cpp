#include <GLEW/glew.h>
#include "VertexBuffer.h"
#include "../log.h"
#include <string>

VertexBuffer::VertexBuffer(const void* data, unsigned int size, unsigned int count)
	: _count(count)
{
	glGenBuffers(1, &m_renderer_id); // Number of buffers, address of the buffers' name
	glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id); // Bind the buffer to a buffer type
	set_data(data, size);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_renderer_id);
	log("Destroyed VertexBuffer (" + std::to_string(m_renderer_id) + ")");
}

void VertexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id); // Bind the buffer to a buffer type
}

void VertexBuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind
}

unsigned int VertexBuffer::count() const
{
	return _count;
}

void VertexBuffer::set_data(const void* data, unsigned int size) const
{
	bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
