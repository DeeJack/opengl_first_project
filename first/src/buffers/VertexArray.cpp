#include "VertexArray.h"
#include <string>

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &_array_id);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &_array_id);
	log("Destroyed VertexArray (" + std::to_string(_array_id) + ")");
}

void VertexArray::bind() const
{
	glBindVertexArray(_array_id);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::add_buffer(VertexBuffer& vb, BufferLayout& layout)
{
	bind();
	vb.bind();
	_bound_vertex = &vb;
	_bound_layout = &layout;
	const auto& elements = layout.get_elements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i != elements.size(); ++i)
	{
		auto stride_test = layout.get_stride();
		const auto& element = elements[i];
		glEnableVertexAttribArray(i); // Enable the attribute
		// Specify the layout of this vertex buffer
		glVertexAttribPointer(i, element.count, element.type, element.normalized, 
			layout.get_stride(), reinterpret_cast<void*>(offset));
		offset += element.count * BufferLayoutElement::size_of_type(element.type);
	}
}

VertexBuffer* VertexArray::bound_buffer() const
{
	return _bound_vertex;
}

BufferLayout* VertexArray::bound_layout() const
{
	return _bound_layout;
}
