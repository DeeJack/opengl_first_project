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

void Renderer::clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}
