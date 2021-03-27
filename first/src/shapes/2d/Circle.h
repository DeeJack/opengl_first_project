#pragma once
#include "../Shape.h"

constexpr float PI = 3.1415926F;
class Circle : public Shape
{
private:
	std::vector<float> _vertexes;
	float _radius;
	glm::vec2 _center;
public:
	Circle(glm::vec2 center, float radius)
		: _radius(radius), _center(center)
	{
		for (float angle = 0.0F; angle < 2.0F * PI; angle += 0.1)
		{
			_vertexes.emplace_back(radius * cos(angle) + center.x);
			_vertexes.emplace_back(radius * sin(angle) + center.y);
		}
		auto* va = new VertexArray();
		auto* vb = new VertexBuffer(&_vertexes[0], _vertexes.size() * sizeof(float), _vertexes.size() / 2);
		auto* layout = new BufferLayout();
		layout->push<float>(2);
		va->add_buffer(*vb, *layout);
		set_vertex_array(va);
	}
	
	void set_position(const float positions[]) override {}

	void set_position(const glm::vec2 newCenter) override
	{
		_vertexes.clear();
		_vertexes.shrink_to_fit();
		for (float angle = 0.0F; angle < 2.0F * PI; angle += 0.1)
		{
			_vertexes.emplace_back(_radius * cos(angle) + _center.x);
			_vertexes.emplace_back(_radius * sin(angle) + _center.y);
		}
		vertex_array()->bind();
		vertex_array()->bound_buffer()->bind();
		vertex_array()->bound_buffer()->change_data(&_vertexes[0], _vertexes.size() * sizeof(float));
	}
	
	void add_data(const float* data, unsigned int count) override
	{
		std::vector<float> fullData;
		int index = 0;
		for (int i = 0; i != static_cast<int>(_vertexes.size() + count); i += 4)
		{
			fullData.emplace_back(_vertexes[index]);
			fullData.emplace_back(_vertexes[index + 1]);
			fullData.emplace_back(data[index]);
			fullData.emplace_back(data[index + 1]);
			index += 2;
		}
		VertexBuffer::unbind();
		delete vertex_array()->bound_buffer();
		auto* vb = new VertexBuffer(&fullData[0], fullData.size() * sizeof(float));
		auto* layout = new BufferLayout();
		layout->push<float>(2);
		layout->push<float>(2);
		vertex_array()->add_buffer(*vb, *layout);
	}
};
