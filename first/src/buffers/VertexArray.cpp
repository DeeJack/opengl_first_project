#include "VertexArray.h"
#include <string>

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &_renderer_id);
}

VertexArray::~VertexArray()
{
	log("Destroyed VertexArray (" + std::to_string(_renderer_id) + ")");
	glDeleteVertexArrays(1, &_renderer_id);
}

void VertexArray::bind() const
{
	glBindVertexArray(_renderer_id);
}

void VertexArray::unbind()
{
	glBindVertexArray(0);
}

void VertexArray::add_buffer(const VertexBuffer& vb, const BufferLayout& layout)
{
	VertexBuffer::unbind();
	bind();
	vb.bind();
	_vertices_count = vb.vertices_count();
	const auto& elements = layout.get_elements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i != elements.size(); ++i)
	{
		const auto& element = elements[i];
		glEnableVertexAttribArray(i); // Enable the attribute
		// Specify the layout of this vertex buffer
		glVertexAttribPointer(i, element.count, element.type, element.normalized, 
			layout.get_stride(), reinterpret_cast<void*>(offset));
		offset += element.count * BufferLayoutElement::size_of_type(element.type);
	}
}

unsigned VertexArray::vertices_count() const
{
	return _vertices_count;
}
