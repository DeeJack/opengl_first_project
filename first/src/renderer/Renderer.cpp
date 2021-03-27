#include "Renderer.h"
#include <GLEW/glew.h>
#include <iostream>

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.bind();
	va.bind();
	ib.bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib.get_count(), GL_UNSIGNED_INT, nullptr)); // The indices pointer is already bound
}

void Renderer::draw(Shape& shape, Shader& shader) const
{
	shader.bind();
	const auto& color = shape.color();
	shader.set_uniform4f("u_color", color.r, color.g, color.b, color.a);
	shape.vertex_array()->bind();
	shape.index_buffer()->bind();
	GLCall(glDrawElements(GL_TRIANGLES, shape.index_buffer()->get_count(), GL_UNSIGNED_INT, nullptr)); // The indices pointer is already bound
}

void Renderer::draw_no_color(Shape& shape, Shader& shader) const
{
	shader.bind();
	const auto& color = shape.color();
	shader.set_uniform4f("u_color", color.r, color.g, color.b, color.a);
	shape.vertex_array()->bind();
	shape.index_buffer()->bind();
	GLCall(glDrawElements(GL_LINE_LOOP, shape.index_buffer()->get_count(), GL_UNSIGNED_INT, nullptr)); // The indices pointer is already bound
}

void Renderer::draw_without_indexes(Shape& shape, Shader& shader) const
{
	shader.bind();
	const auto& color = shape.color();
	shader.set_uniform4f("u_color", color.r, color.g, color.b, color.a);
	shape.vertex_array()->bind();
	GLCall(glDrawArrays(GL_TRIANGLES, 0, shape.vertex_array()->bound_buffer()->vertices_count())); // The indices pointer is already bound
}

void Renderer::draw_without_indexes_no_color(Shape& shape, Shader& shader) const
{
	shader.bind();
	const auto& color = shape.color();
	shader.set_uniform4f("u_color", color.r, color.g, color.b, color.a);
	shape.vertex_array()->bind();
	GLCall(glDrawArrays(GL_LINE_LOOP, 0, shape.vertex_array()->bound_buffer()->vertices_count())); // The indices pointer is already bound
}

void Renderer::draw_without_indexes_triangle_fan(Shape& shape, Shader& shader) const
{
	shader.bind();
	const auto& color = shape.color();
	shader.set_uniform4f("u_color", color.r, color.g, color.b, color.a);
	shape.vertex_array()->bind();
	GLCall(glDrawArrays(GL_TRIANGLE_FAN, 0, shape.vertex_array()->bound_buffer()->vertices_count())); // The indices pointer is already bound
}

void Renderer::clear() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
