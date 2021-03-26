#include "Renderer.h"
#include <GLEW/glew.h>
#include <iostream>

void GLAPIENTRY LOG_ERROR(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	if (type == 33361) // || type == 33356
		return;
	std::cout << "[OpenGL Error](" << type << ") " << message << std::endl;
	std::cout << source << ", type: " << type << ", id: " << id << ", severity: " << severity << ", message: " << message << std::endl;
	__debugbreak();
}

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.bind();
	va.bind();
	ib.bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib.get_count(), GL_UNSIGNED_INT, nullptr)); // The indices pointer is already bound
}

void Renderer::draw(Shape& shape) const
{
	shape.shader()->bind();
	const glm::vec4 color = shape.color();
	shape.shader()->set_uniform4f("u_color", color.r, color.g, color.b, color.a);
	shape.vertex_array()->bind();
	shape.index_buffer()->bind();
	GLCall(glDrawElements(GL_TRIANGLES, shape.index_buffer()->get_count(), GL_UNSIGNED_INT, nullptr)); // The indices pointer is already bound
}

void Renderer::drawNoColor(Shape& shape) const
{
	shape.shader()->bind();
	const glm::vec4 color = shape.color();
	shape.shader()->set_uniform4f("u_color", color.r, color.g, color.b, color.a);
	shape.vertex_array()->bind();
	shape.index_buffer()->bind();
	GLCall(glDrawElements(GL_LINE_LOOP, shape.index_buffer()->get_count(), GL_UNSIGNED_INT, nullptr)); // The indices pointer is already bound
}

void Renderer::drawWithoutIndexes(Shape& shape) const
{
	shape.shader()->bind();
	const glm::vec4 color = shape.color();
	shape.shader()->set_uniform4f("u_color", color.r, color.g, color.b, color.a);
	shape.vertex_array()->bind();
	GLCall(glDrawArrays(GL_TRIANGLES, 0, shape.vertex_array()->bound_buffer()->count())); // The indices pointer is already bound
}

void Renderer::drawWithoutIndexesNoColor(Shape& shape) const
{
	shape.shader()->bind();
	const glm::vec4 color = shape.color();
	shape.shader()->set_uniform4f("u_color", color.r, color.g, color.b, color.a);
	shape.vertex_array()->bind();
	GLCall(glDrawArrays(GL_LINE_LOOP, 0, shape.vertex_array()->bound_buffer()->count())); // The indices pointer is already bound
}

void Renderer::clear() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
