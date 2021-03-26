#pragma once
#include "../../Shape.h"
#include "glm/vec2.hpp"

class Pentagon : public Shape
{
private:
	float* _positions = new float[5 * 2];
public:
	Pentagon(const glm::vec2 vertexes[5], Shader* shader) : Shape()
	{
		for (int i = 0; i < 5; i++)
		{
			_positions[i * 2] = vertexes[i].x * 2;
			_positions[i * 2 + 1] = vertexes[i].y * 2;
		}
		auto va = new VertexArray();
		auto vb = new VertexBuffer(_positions, 5 * 2 * sizeof(float));
		BufferLayout* layout = new BufferLayout();
		layout->push<float>(2);
		va->add_buffer(*vb, *layout);
		const unsigned int indexes[] = { 
			0, 1, 2, // ABC
			0, 2, 3, // ACD
			0, 3, 4, // ADE
		};
		IndexBuffer* ib = new IndexBuffer(indexes, 3 * 3);
		set_index_buffer(ib);
		set_vertex_array(va);
		set_shader(shader);
	}

	virtual ~Pentagon()
	{
		delete _positions;
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
};
