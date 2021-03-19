#pragma once
#include "VertexBuffer.h"
#include "layout/BufferLayout.h"

class VertexArray
{
private:
	unsigned int _array_id;
public:
	VertexArray();
	VertexArray(const VertexArray& va) = delete;
	~VertexArray();

	void bind() const;
	void unbind() const;

	void add_buffer(const VertexBuffer& vb, const BufferLayout& layout);
};