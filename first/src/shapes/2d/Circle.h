#pragma once
#include "../Shape.h"

class Circle : public Shape
{
private:
	std::vector<float> _vertexes;
public:
	Circle(glm::vec2 center, float radius, Shader* shader)
	{
		const float PI = 3.1415926F;
		for (float angle = 0.0F; angle < 2.0F * PI; angle += 0.1)
		{
			_vertexes.emplace_back(radius * cos(angle) + center.x);
			_vertexes.emplace_back(radius * sin(angle) + center.y);
		}

		auto va = new VertexArray();
		auto vb = new VertexBuffer(&_vertexes[0], _vertexes.size() * sizeof(float), _vertexes.size() / 2);
		BufferLayout* layout = new BufferLayout();
		layout->push<float>(2);
		va->add_buffer(*vb, *layout);
		set_vertex_array(va);
		set_shader(shader);
	}
	
	void set_position(const float positions[]) override {}
	void set_position(const glm::vec2 newBotLeft) override {}
	void add_data(const float* data, unsigned count) override {}
};
