#pragma once
class VertexBuffer
{
private:
	unsigned int m_renderer_id;
public:
	VertexBuffer(const void* data, unsigned int size);
	VertexBuffer(const VertexBuffer&) = delete;
	~VertexBuffer();

	void bind() const;

	void unbind() const;

	void set_data(const void* data, unsigned int size);
};