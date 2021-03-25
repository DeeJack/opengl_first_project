#pragma once
#include "VertexBuffer.h"
#include "layout/BufferLayout.h"

class VertexArray
{
private:
	unsigned int _array_id;
	VertexBuffer* _bound_vertex;
	BufferLayout* _bound_layout;
public:
	VertexArray();
	VertexArray(const VertexArray& va) = delete;
	~VertexArray();

	void bind() const;
	void unbind() const;

	void add_buffer(VertexBuffer& vb, BufferLayout& layout);
	VertexBuffer* bound_buffer();
	BufferLayout* bound_layout();
};