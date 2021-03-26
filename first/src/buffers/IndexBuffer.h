#pragma once
class IndexBuffer
{
private:
	unsigned int _renderer_id = 0;
	unsigned int _indices_count;
public:
	IndexBuffer(const unsigned int* data, const unsigned int count);
	IndexBuffer(const IndexBuffer&) = delete;
	~IndexBuffer();

	void bind() const;
	static void unbind();

	unsigned int get_count() const;

	IndexBuffer& operator=(const IndexBuffer&) = delete;
};