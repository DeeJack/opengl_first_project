#pragma once
#include "../buffers/VertexArray.h"
#include "../buffers/IndexBuffer.h"
#include "../shaders/Shader.h"

class Renderer
{
private:
public:
	void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;

	void clear() const;
};