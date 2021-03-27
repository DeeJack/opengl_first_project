#pragma once
#include "VertexBuffer.h"
#include "layout/BufferLayout.h"

class VertexArray
{
private:
	unsigned int _renderer_id;
	VertexBuffer* _bound_buffer;
	BufferLayout* _bound_layout;
public:
	VertexArray();
	VertexArray(const VertexArray& va) = delete;
	~VertexArray();

	void bind() const;
	static void unbind();

	void add_buffer(VertexBuffer& vb, BufferLayout& layout);

	VertexBuffer* bound_buffer() const;
	BufferLayout* bound_layout() const;
	
	VertexArray& operator=(const VertexArray&) = delete;
};