#include <GLEW/glew.h>
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	glGenBuffers(1, &m_renderer_id); // Number of buffers, address of the buffers' name
	glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id); // Bind the buffer to a buffer type
	set_data(data, size);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_renderer_id);
}

void VertexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id); // Bind the buffer to a buffer type
}

void VertexBuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind
}

void VertexBuffer::set_data(const void* data, unsigned size)
{
	bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
