#include "IndexBuffer.h"

#include "../log.h"
#include <string>

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) : m_count(count)
{
	ASSERT(sizeof(unsigned int) == sizeof(GLuint));
	
	glGenBuffers(1, &m_renderer_id); // Number of buffers, address of the buffers' name
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id); // Bind the buffer to a buffer type
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_renderer_id);
	log("Destroyed IndexBuffer (" + std::to_string(m_renderer_id) + ")");
}

void IndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id); // Bind the buffer to a buffer type
}

void IndexBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Bind the buffer to a buffer type
}
