#pragma once
#include "../buffers/VertexArray.h"
#include "../buffers/IndexBuffer.h"
#include "../shaders/Shader.h"
#include "../shapes/Shape.h"

class Renderer
{
public:
	void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	void draw(Shape& shape, Shader& shader) const;
	void draw_no_color(Shape& shape, Shader& shader) const;
	void draw_without_indexes(Shape& shape, Shader& shader) const;
	void draw_without_indexes_no_color(Shape& shape, Shader& shader) const;
	void draw_without_indexes_triangle_fan(Shape& shape, Shader& shader) const;

	void clear() const;
};
