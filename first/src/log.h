#pragma once
#include <GLEW/glew.h>
#include <iostream>

#define ASSERT(x) if (!(x)) __debugbreak()

static void log(const std::string& s)
{
	std::cout << s << std::endl;
}

void GLAPIENTRY LOG_ERROR(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

#define GLCall(x) GLClearErrors();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

static void GLClearErrors()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line)
{
	while (const auto error = glGetError())
	{
		std::cout << "[OpenGL ERROR]: " << error << ", " << function <<
			"; file: " << file << "; line: " << line << std::endl;
		return false;
	}
	return true;
}