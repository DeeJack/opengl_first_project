#include <GLEW/glew.h>
#include "VertexBuffer.h"
#include "../log.h"
#include <string>

VertexBuffer::VertexBuffer(const void* data, const unsigned int size, const unsigned int vertices_count)
	: _vertices_count(vertices_count)
{
	glGenBuffers(1, &_renderer_id); // Number of buffers, address of the buffers' name
	bind();
	glBufferStorage(GL_ARRAY_BUFFER, size, 0, GL_MAP_WRITE_BIT | GL_MAP_READ_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
	change_data(data, size);
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

void VertexBuffer::change_data(const void* data, const unsigned int size) const
{
	bind();
	float* ptr = (float*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
	//glNamedBufferSubData(_renderer_id, 0, size, data);
	memcpy(ptr, data, size);
	glUnmapBuffer(GL_ARRAY_BUFFER);
	//bind();
	//glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

//void VertexBuffer::change_data(const void* data, unsigned int size) const
//{
	//bind();
	//float* ptr = (float*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
	//glNamedBufferSubData(_renderer_id, 0, size, data);
	//memcpy(ptr, data, size);
	//glUnmapBuffer(GL_ARRAY_BUFFER);
//}
