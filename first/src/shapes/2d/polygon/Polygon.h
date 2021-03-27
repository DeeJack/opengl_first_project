#pragma once
#include "../../Shape.h"

class Polygon : public Shape
{
public:
	Polygon(const std::vector<glm::vec2>& positions) : Shape()
	{
		std::vector<float> _positions;
		std::vector<unsigned int> indices;
		for (int i = 0; i < positions.size(); i++)
		{
			_positions.emplace_back(positions[i].x);
			_positions.emplace_back(positions[i].y);
		}
		for (int i = 0; i < static_cast<int>(positions.size() - 2); i++)
		{
			indices.emplace_back(0);
			indices.emplace_back(i + 1);
			indices.emplace_back(i + 2);
		}
		auto* va = new VertexArray();
		auto* vb = new VertexBuffer(&_positions[0], static_cast<int>(_positions.size()) * sizeof(float), _positions.size() / 2);
		auto* layout = new BufferLayout();
		layout->push<float>(2);
		va->add_buffer(*vb, *layout);
		auto* ib = new IndexBuffer(&indices[0], indices.size());
		set_index_buffer(ib);
		set_vertex_array(va);
	}

	Polygon() = default;
	
	void set_position(const float positions[]) override {}
	void set_position(const glm::vec2 newBotLeft) override {}
	void add_data(const float* data, unsigned count) override {}
};
