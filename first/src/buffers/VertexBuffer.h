#pragma once
class VertexBuffer
{
private:
	unsigned int _renderer_id = 0;
	unsigned int _vertices_count = 0;
public:
	/*
	 * data: the array of vertices
	 * size: the size of the array
	 * vertices_count: the count of the vertices, use only if you want to draw without indices
	 */
	VertexBuffer(const void* data, unsigned int size, unsigned int vertices_count = 0);
	VertexBuffer(const VertexBuffer&) = delete; // Copy of the object not allowed!
	~VertexBuffer();

	void bind() const;
	static void unbind();

	unsigned int vertices_count() const;

	void set_data(const void* data, unsigned int size) const;

	VertexBuffer& operator=(const VertexBuffer&) = delete; // Copy assignment not allowed
};