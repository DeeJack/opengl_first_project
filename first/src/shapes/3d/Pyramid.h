#pragma once
#include "../Shape.h"

class Pyramid : public Shape
{
private:
	std::vector<float> _positions;
public:
	Pyramid(const glm::vec3 firstBase, const glm::vec3 secondBase, const glm::vec3 top): Shape(DrawType::INDICES)
	{
		_positions = {
			firstBase.x, firstBase.y, firstBase.z, // A (first) 0
			secondBase.x, firstBase.y, firstBase.z, // B 1
			secondBase.x, secondBase.y, secondBase.z, // C 2 (second)
			firstBase.x, secondBase.y, secondBase.z, // D 3
			top.x, top.y, top.z, // E 4 (top)
		};
		auto* va = new VertexArray();
		auto* vb = new VertexBuffer(&_positions[0], 5 * 3 * sizeof(float));
		auto* layout = new BufferLayout();
		layout->push<float>(3); // Coords
		va->add_buffer(*vb, *layout);
		const unsigned int indexes[] = {
			0, 1, 3, // ABD
			0, 1, 3, // ABD,
			1, 2, 4, // BEC
			3, 2, 4, // DCE
			0, 3, 4, // ADE
			0, 1, 4,// ABE
		};
		auto* ib = new IndexBuffer(indexes, 6 * 3);
		set_index_buffer(ib);
		set_vertex_array(va);
	}

	void set_position(const float positions[]) override {}
	void set_position(const glm::vec2 newBotLeft) override {}
	
	void add_data(const float* data, unsigned int count) override {
		std::vector<float> fullData;
		const int dataPerVertex = count / (_positions.size() / 3);
		int index = 0, index2 = 0;
		for (int i = 0; i < static_cast<int>(_positions.size() + count); i += (3 + dataPerVertex))
		{
			fullData.emplace_back(_positions[index]);
			fullData.emplace_back(_positions[index + 1]);
			fullData.emplace_back(_positions[index + 2]);
			index += 3;
			for (int j = 0; j < dataPerVertex; j++)
			{
				fullData.emplace_back(data[index2]);
				index2++;
			}
		}
		for (int i = 1; i < static_cast<int>((_positions.size()  + count + 1)); ++i)
		{
			std::cout << fullData[i - 1] << ", ";
			if (i % (3 + dataPerVertex) == 0)
			{
				std::cout << "\n";
			}
		}
		auto* vb = new VertexBuffer(&fullData[0], fullData.size() * sizeof(float), _positions.size() / 3);
		auto* layout = new BufferLayout();
		layout->push<float>(3);
		layout->push<float>(dataPerVertex);
		vertex_array()->add_buffer(*vb, *layout);
	}
};
