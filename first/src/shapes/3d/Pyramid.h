#pragma once
#include "../Shape.h"

class Pyramid : public Shape
{
private:
	float* _positions;
public:
	Pyramid(glm::vec3 firstBase, glm::vec3 secondBase, glm::vec3 top, Shader* shader)
	{
		_positions = new float[] {
			firstBase.x, firstBase.y, firstBase.z, 1.F, 0.F, 0.F,// A (first) 0
			secondBase.x, firstBase.y, firstBase.z, 1.F, 0.3F, 0.F,// B 1
			secondBase.x, secondBase.y, secondBase.z, 1.F, 0.6F, 0.F,// C 2 (second)
			firstBase.x, secondBase.y, secondBase.z, 0.5F, 1.F, 0.F,// D 3
			top.x, top.y, top.z, 0.6F, 0.F, 1.F,// E 4 (top)
		};
		auto* va = new VertexArray();
		auto* vb = new VertexBuffer(_positions, 5 * 6 * sizeof(float));
		auto* layout = new BufferLayout();
		layout->push<float>(3); // Coords
		layout->push<float>(3); // Colors
		va->add_buffer(*vb, *layout);
		const unsigned int indexes[] = {
			0, 1, 3, // ABD
			0, 1, 3, // ABD,
			1, 2, 4, // BEC
			3, 2, 4, // DCE
			0, 3, 4, // ADE
			0, 1, 4,// ABE
		};
		IndexBuffer* ib = new IndexBuffer(indexes, 6 * 3);
		set_index_buffer(ib);
		set_vertex_array(va);
		set_shader(shader);
	}

	void set_position(const float positions[]) override {}
	void set_position(const glm::vec2 newBotLeft) override {}
	void add_data(const float* data, unsigned size) override {}
};
