#pragma once
#include "../../Shape.h"
#include "glm/vec2.hpp"
#include <array>

class Pentagon : public Shape
{
public:
	Pentagon(const glm::vec2 vertexes[5]) : Shape(DrawType::INDICES)
	{
		std::array<float, 10> _positions;
		for (int i = 0; i < 5; i++)
		{
			_positions[i * 2] = vertexes[i].x * 2;
			_positions[i * 2 + 1] = vertexes[i].y * 2;
		}
		auto* va = new VertexArray();
		auto* vb = new VertexBuffer(&_positions[0], 5 * 2 * sizeof(float));
		auto* layout = new BufferLayout();
		layout->push<float>(2);
		va->add_buffer(*vb, *layout);
		const unsigned int indexes[] = { 
			0, 1, 2, // ABC
			0, 2, 3, // ACD
			0, 3, 4, // ADE
		};
		auto* ib = new IndexBuffer(indexes, 3 * 3);
		set_index_buffer(ib);
		set_vertex_array(va);
	}

	void set_position(const glm::vec2 newBotLeft) override
	{
	}

	void set_position(const float positions[8]) override
	{
	}

	void add_data(const float* data, unsigned count) override
	{
	}

	bool intersect(const glm::vec2& point) override
	{
		return false;
	}

	bool intersect(const Shape& otherShape) override
	{
		return false;
	}
};
