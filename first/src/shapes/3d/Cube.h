#pragma once
#include "../Shape.h"

class Cube : public Shape
{
private:
	float* _positions;
public:
	Cube(glm::vec3 first, glm::vec3 second, Shader* shader)
	{
		_positions = new float[] {
			first.x, first.y, first.z, 1.F, 0.F, 0.F,// A (first) 0
				second.x, first.y, first.z, 1.F, 0.3F, 0.F,// B 1
				second.x, second.y, first.z, 1.F, 0.6F, 0.F,// C 2
				first.x, second.y, first.z, 0.5F, 1.F, 0.F,// D 3
				second.x, first.y, second.z, 0.F, 1.F, 0.F,// E 4
				second.x, second.y, second.z, 0.F, 1.F, 1.F,// F 5(second)
				first.x, first.y, second.z, 0.F, 0.6F, 1.F,// G 6
				first.x, second.y, second.z, 0.6F, 0.F, 1.F,// H 7
		};
		auto* va = new VertexArray();
		auto* vb = new VertexBuffer(_positions, 8 * 6 * sizeof(float));
		auto* layout = new BufferLayout();
		layout->push<float>(3); // Coords
		layout->push<float>(3); // Colors
		va->add_buffer(*vb, *layout);
		const unsigned int indexes[] = {
			0, 1, 3, // ABD
			1, 2, 3, // BCD,
			1, 4, 2, // BEC
			4, 5, 2, // EFC
			4, 5, 7, // EFH
			4, 7, 6,// EHG
			6, 7, 3,// GHD
			6, 3, 0,// GDA
			2, 5, 7, // CFH
			2, 3, 7, // CDH
			0, 1, 6, //ABG
			1, 4, 6// BEG
		};
		IndexBuffer* ib = new IndexBuffer(indexes, 12 * 3);
		set_index_buffer(ib);
		set_vertex_array(va);
		set_shader(shader);
	}

	void set_position(const float positions[]) override {}
	void set_position(const glm::vec2 newBotLeft) override {}
	void add_data(const float* data, unsigned size) override {}
};
