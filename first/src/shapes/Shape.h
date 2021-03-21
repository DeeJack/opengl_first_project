#pragma once
#include "../buffers/IndexBuffer.h"
#include "../buffers/VertexArray.h"
#include "../buffers/VertexBuffer.h"
#include "../shaders/Shader.h"

#include "glm/glm.hpp"
#include "glm/vec4.hpp"

/*
 *
 *	A shape needs to be drawn, so it needs to have a vertex array with the vertexes, an index buffer
 *	Does every shape need a different shader?
 *
 * 
 * Examples of shape: Triangle, Rectangle
 * TODO: add color, default color is white
 * 
 */
class Shape
{
private:
	VertexArray* _vertex_array;
	IndexBuffer* _index_buffer;
	Shader* _shader;
	glm::vec4 _color = glm::vec4(1.F, 1.F, 1.F, 1.F);
public:
	Shape(VertexArray* vertexes, IndexBuffer* buffer, Shader* shader);
	Shape();

	Shape(const Shape&) = delete;
	
	~Shape();

	VertexArray* vertex_array() const;

	void set_vertex_array(VertexArray* const vertex_array);

	IndexBuffer* index_buffer() const;

	void set_index_buffer(IndexBuffer* const index_buffer);

	Shader* shader() const;

	void set_shader(Shader* shader);

	void set_color(const glm::vec4& color);

	glm::vec4& color();

	virtual void set_position(const float positions[]) = 0;
	virtual void set_position(const glm::vec2 newBotLeft) = 0;
};
