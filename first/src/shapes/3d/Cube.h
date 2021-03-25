#pragma once
#include "../Shape.h"

class Cube : public Shape
{
private:
	float* _positions;
	//float* _full_data;
public:
	Cube(glm::vec3 first, glm::vec3 second, Shader* shader)
	{
		_positions = new float[] {
			first.x, first.y, first.z,// A (first) 0
				second.x, first.y, first.z, // B 1
				second.x, second.y, first.z, // C 2
				first.x, second.y, first.z, // D 3
				second.x, first.y, second.z, // E 4
				second.x, second.y, second.z, // F 5(second)
				first.x, first.y, second.z, // G 6
				first.x, second.y, second.z, // H 7
		};
		
		const unsigned int indexes[] = {
			0, 1, 3, // ABD
			1, 2, 3, // BCD,
			1, 4, 2, // BEC
			4, 5, 2, // EFC
			4, 5, 7, // EFH
			4, 7, 6, // EHG
			6, 7, 3, // GHD
			6, 3, 0, // GDA
			2, 5, 7, // CFH
			2, 3, 7, // CDH
			0, 1, 6, //ABG
			1, 4, 6 // BEG
		};
		/*_full_data = new float[18 * 6];
		for (int i = 0; i < 36; i += 3) {
			_full_data[i  + 0] = _positions[indexes[i]];
			_full_data[i  + 1] = _positions[indexes[i + 1]];
			_full_data[i  + 2] = _positions[indexes[i + 2]];
		}*/
		auto* va = new VertexArray();
		auto* vb = new VertexBuffer(_positions, 8 * 3 * sizeof(float));
		auto* layout = new BufferLayout();
		layout->push<float>(3); // Coords
		va->add_buffer(*vb, *layout);
		IndexBuffer* ib = new IndexBuffer(indexes, 12 * 3);
		set_index_buffer(ib);
		set_vertex_array(va);
		set_shader(shader);
	}

	void set_position(const float positions[]) override {}
	void set_position(const glm::vec2 newBotLeft) override {}
	void add_data(const float* data, unsigned count) override
	{
		float* fullData = new float[8 * 3 + count];
		int index = 0;
		for (int i = 0; i < 8 * 3 + count; i += 6)
		{
			fullData[i] = _positions[index];
			fullData[i + 1] = _positions[index + 1];
			fullData[i + 2] = _positions[index + 2];
			fullData[i + 3] = data[index];
			fullData[i + 4] = data[index + 1];
			fullData[i + 5] = data[index + 2];
			index += 3;
		}
		for (int i = 1; i < ((8 * 3) + count + 1); ++i)
		{
			std::cout << fullData[i - 1] << ", ";
			if (i % 6 == 0)
				std::cout << "\n";
		}
		vertex_array()->bound_buffer()->unbind();
		delete vertex_array()->bound_buffer();
		auto vb = new VertexBuffer(fullData, (8 * 6) * sizeof(float));
		BufferLayout* layout = new BufferLayout();
		layout->push<float>(3);
		layout->push<float>(3);
		vertex_array()->add_buffer(*vb, *layout);
	}
};
