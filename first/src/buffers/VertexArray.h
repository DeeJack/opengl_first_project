#pragma once
#include "VertexBuffer.h"
#include "layout/BufferLayout.h"

class VertexArray
{
private:
	unsigned int _renderer_id;
	unsigned int _vertices_count = 0; // The number of vertices for the vertex array associated with the array
public:
	VertexArray();
	VertexArray(const VertexArray& va) = delete;
	~VertexArray();

	void bind() const;
	static void unbind();

	void add_buffer(const VertexBuffer& vb, const BufferLayout& layout);

	unsigned int vertices_count() const;

	VertexArray& operator=(const VertexArray&) = delete;
};