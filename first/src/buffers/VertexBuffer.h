#pragma once
class VertexBuffer
{
private:
	unsigned int m_renderer_id;
	unsigned int _count;
public:
	VertexBuffer(const void* data, unsigned int size, unsigned int count = 0);
	VertexBuffer(const VertexBuffer&) = delete;
	~VertexBuffer();

	void bind() const;

	void unbind() const;

	void set_data(const void* data, unsigned int size);
};