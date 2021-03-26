#pragma once
#include <string>
#include <unordered_map>

#include "glm/fwd.hpp"

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
private:
	unsigned int _renderer_id = 0;
	std::string _file_path;
	std::unordered_map<std::string, int> _location_cache;
public:
	explicit Shader(const std::string& file_path);
	~Shader();

	void bind() const;
	static void unbind();

	// Uniform
	void set_uniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void set_uniform_mat4f(const std::string& name, const glm::mat4& matrix);
	void set_uniform1i(const std::string& name, int value);

private:
	unsigned int compile_shader(unsigned int type, const std::string& source);
	unsigned int create_shader(const std::string& vertex_shader, const std::string& fragment_shader);
	ShaderProgramSource parse_shader(const std::string& file_name) const;
	int get_uniform_location(const std::string& name);
};
