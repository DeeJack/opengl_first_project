#include "Shape.h"

Shape::Shape(VertexArray* vertexes, IndexBuffer* buffer) : _vertex_array(vertexes),
_index_buffer(buffer)
{
}

Shape::Shape() = default;

Shape::~Shape()
{
	log("Destroying Shape");
	delete _vertex_array;
	delete _index_buffer;
	log("Destroyed Shape");
}

VertexArray* Shape::vertex_array() const
{
	return _vertex_array;
}

void Shape::set_vertex_array(VertexArray* const vertex_array)
{
	_vertex_array = vertex_array;
}

IndexBuffer* Shape::index_buffer() const
{
	return _index_buffer;
}

void Shape::set_index_buffer(IndexBuffer* const index_buffer)
{
	_index_buffer = index_buffer;
}

void Shape::set_color(const glm::vec4& color)
{
	_color = color;
}

glm::vec4& Shape::color()
{
	return _color;
}
