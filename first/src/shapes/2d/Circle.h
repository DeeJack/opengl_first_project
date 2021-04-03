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
	Circle(const glm::vec2& center, const float radius)
		: Shape(DrawType::TRIANGLE_FAN), _radius(radius), _center(center)
	{
		_vertexes.emplace_back(center.x);
		_vertexes.emplace_back(center.y);
		for (int angle = 0; angle <= 360; angle += 10)
		{
			_vertexes.emplace_back(radius * cos(glm::radians(static_cast<float>(angle))) + center.x);
			_vertexes.emplace_back(radius * sin(glm::radians(static_cast<float>(angle))) + center.y);
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
		_vertexes.emplace_back(newCenter.x);
		_vertexes.emplace_back(newCenter.y);
		for (int angle = 0; angle < 360; angle += 10)
		{
			_vertexes.emplace_back(_radius * cos(glm::radians(static_cast<float>(angle))) + _center.x);
			_vertexes.emplace_back(_radius * sin(glm::radians(static_cast<float>(angle))) + _center.y);
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

	bool intersect(const glm::vec2& point) override
	{
		return false;
	}
	
	bool intersect(const Shape& otherShape) override
	{
		return false;
	}


	float radius() const;
	glm::vec2 center() const;

	std::vector<float> vertexes() const;
};

inline float Circle::radius() const
{
	return _radius;
}

inline glm::vec2 Circle::center() const
{
	return _center;
}

inline std::vector<float> Circle::vertexes() const
{
	return _vertexes;
}
