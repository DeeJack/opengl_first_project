#include "Shader.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <GLEW/glew.h>

#include "../log.h"
#include "glm/gtc/matrix_transform.hpp"

Shader::Shader(const std::string& file_path)
	: _file_path(file_path)
{
	const auto source = parse_shader(file_path);
	_renderer_id = create_shader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
	unbind();
	glDeleteProgram(_renderer_id);
	log("Destroyed Shader (" + std::to_string(_renderer_id) + ")");
}

void Shader::bind() const
{
	glUseProgram(_renderer_id);
}

void Shader::unbind()
{
	glUseProgram(0);
}

void Shader::set_uniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	glUniform4f(get_uniform_location(name), v0, v1, v2, v3);
}

void Shader::set_uniform1b(const std::string& name, bool value)
{
	glUniform1f(get_uniform_location(name), value ? 1.F : 0.F);
}

void Shader::set_uniform_mat4f(const std::string& name, const glm::mat4& matrix)
{
	glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::set_uniform1i(const std::string& name, int value)
{
	glUniform1i(get_uniform_location(name), value);
}

int Shader::get_uniform_location(const std::string& name)
{
	if (_location_cache.find(name) != _location_cache.end())
		return _location_cache[name];
	
	const int location = glGetUniformLocation(_renderer_id, name.c_str()); // Get the location of the uniform
	if (location == -1)
		std::cout << "Warning: uniform " << name << " doesn't exists!\n";
	_location_cache[name] = location;
	return location;
}

unsigned int Shader::compile_shader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type); // Create the shader, return the ID of the shader
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr); // Put the source in the shader, the strings are "NULL" terminated
	glCompileShader(id); // Compile the code of the given shader

	int result;
	// iv -> int and vector
	// Check the status of a certain parameter for the given shader. The result is stored in "result"
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		auto* message = static_cast<char*>(_malloca(length * sizeof(char)));
		//auto* message = static_cast<char*>(alloca(length * sizeof(char)));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "FAILED TO COMPILE " <<
			(type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " SHADER!" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

ShaderProgramSource Shader::parse_shader(const std::string& file_name) const
{
	std::ifstream stream(file_name);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (std::getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[static_cast<int>(type)] << line << '\n';
		}
	}
	return { ss[0].str(), ss[1].str() };
}

/*
 * Vertex shader: the position of the vertex that needs to be drawn on the screen
 * Fragment shader (or pixel shader): the color of the pixels
 */
unsigned int Shader::create_shader(const std::string& vertex_shader, const std::string& fragment_shader)
{
	// Create a program object, that is an object to which shader objects can be attached
	const unsigned int program = glCreateProgram();
	// Create and compile the 2 shaders
	const unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertex_shader);
	const unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fragment_shader);

	// Attach the shaders to the program
	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));

	//Links the program object, if any shader objects are attached to program, they will be used to create an executable
	GLCall(glLinkProgram(program));

	// Checks to see whether the executables contained in program can execute in the current OpenGL state.
	GLCall(glValidateProgram(program));

	// Frees the memory and invalidates the name associated with the shader object
	// If a shader object is attached to a program object, it will be flagged for deletion
	// but it won't be deleted until the program is no longer attached to the shader.
	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return program;
}