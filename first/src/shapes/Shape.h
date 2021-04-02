#pragma once
#include "../buffers/IndexBuffer.h"
#include "../buffers/VertexArray.h"

#include "glm/glm.hpp"
#include "glm/vec4.hpp"

enum class DrawType : char
{
	INDICES = 0, NO_INDICES = 1, TRIANGLE_FAN = 2 
};

class Shape
{
private:
	VertexArray* _vertex_array = nullptr;
	IndexBuffer* _index_buffer = nullptr;
	glm::vec4 _color = glm::vec4(1.F, 1.F, 1.F, 1.F);
	DrawType _draw_type;
public:
	Shape(VertexArray* vertexes, IndexBuffer* buffer, DrawType draw_type);
	Shape(DrawType draw_type);

	Shape(const Shape&) = delete;

	virtual ~Shape();

	VertexArray* vertex_array() const;

	void set_vertex_array(VertexArray* const vertex_array);

	IndexBuffer* index_buffer() const;

	void set_index_buffer(IndexBuffer* const index_buffer);

	void set_color(const glm::vec4& color);
	glm::vec4& color();


	DrawType draw_type() const;
	void set_draw_type(const DrawType draw_type);
	
	virtual void set_position(const float positions[]) = 0;
	virtual void set_position(const glm::vec2 newPoint) = 0;

	virtual void add_data(const float* data, unsigned count) = 0;

	virtual bool intersect(const glm::vec2& point)
	{
		return false;
	}
	
	virtual bool intersect(const Shape& otherShape)
	{
		return false;
	}
};
