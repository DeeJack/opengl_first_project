#pragma once
#include "../Shape.h"
#include "glm/vec2.hpp"

class Triangle : public Shape
{
private:
public:
	Triangle(const glm::vec2& first, const glm::vec2& second, const glm::vec2& third, Shader* shader) : Shape()
	{
		const unsigned int indexes[] = { 0 , 1, 2 };
		IndexBuffer* ib = new IndexBuffer(indexes, 3);
		const float positions[] = { first.x, first.y, second.x, second.y, third.x, third.y };
		auto va = new VertexArray();
		auto vb = new VertexBuffer(positions, 3 * 2 * sizeof(float));
		BufferLayout layout;
		layout.push<float>(2);
		va->add_buffer(*vb, layout);
		set_index_buffer(ib);
		set_vertex_array(va);
		set_shader(shader);
	}


	void set_position(const float positions[]) override
	{
		
	}

	void set_position(const glm::vec2 newBotLeft) override
	{
		
	}
};
