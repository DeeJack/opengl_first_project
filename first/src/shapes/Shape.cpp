#include "Shape.h"

Shape::Shape(VertexArray* vertexes, IndexBuffer* buffer, Shader* shader) : _vertex_array(vertexes),
_index_buffer(buffer), _shader(shader)
{
}

Shape::Shape() : _vertex_array(nullptr), _index_buffer(nullptr), _shader(nullptr)
{
}

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

Shader* Shape::shader() const
{
	return _shader;
}

void Shape::set_shader(Shader* shader)
{
	_shader = shader;
}

void Shape::set_color(const glm::vec4& color)
{
	_color = color;
}

glm::vec4& Shape::color()
{
	return _color;
}
