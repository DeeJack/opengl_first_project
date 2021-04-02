#pragma once
#include "../Shape.h"
#include "glm/vec2.hpp"

class Triangle : public Shape
{
public:
	Triangle(const glm::vec2& first, const glm::vec2& second, const glm::vec2& third) : Shape()
	{
		const float positions[] = { first.x, first.y, second.x, second.y, third.x, third.y };
		const unsigned int indexes[] = { 0 , 1, 2 };
		auto* ib = new IndexBuffer(indexes, 3);
		auto* va = new VertexArray();
		auto* vb = new VertexBuffer(positions, 3 * 2 * sizeof(float));
		auto* layout = new BufferLayout();
		layout->push<float>(2);
		va->add_buffer(*vb, *layout);
		set_index_buffer(ib);
		set_vertex_array(va);
	}

	void set_position(const float positions[]) override
	{
	}

	void set_position(const glm::vec2 newBotLeft) override
	{
	}

	void add_data(const float* data, unsigned size) override
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
