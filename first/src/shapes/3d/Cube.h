#pragma once
#include "../Shape.h"

class Cube : public Shape
{
private:
	std::vector<float> _positions;
	std::vector<float> _full_data;
	int _vertexes;

	const unsigned int indexes[36] = {
		0, 1, 3, // ABD
		1, 2, 3, // BCD,
		1, 4, 2, // BEC
		4, 5, 2, // EFC
		4, 5, 6, // EFG
		5, 7, 6, // FHG
		6, 0, 7, // GAH
		0, 3, 7, // ADH
		3, 2, 7, // DCH
		2, 5, 7, // CFH
		0, 1, 6, // ABG
		1, 4, 6 // BEG
	};
public:
	Cube(glm::vec3 first, glm::vec3 second, Shader* shader)
	{
		_positions = {
			first.x, first.y, first.z,// A (first) 0
			second.x, first.y, first.z, // B 1
			second.x, second.y, first.z, // C 2
			first.x, second.y, first.z, // D 3
			second.x, first.y, second.z, // E 4
			second.x, second.y, second.z, // F 5(second)
			first.x, first.y, second.z, // G 6
			first.x, second.y, second.z // H 7
		};
		set_shader(shader);
	}

	void fillWithIndexes()
	{
		_vertexes = 8;
		_full_data = _positions;
		auto* va = new VertexArray();
		auto* vb = new VertexBuffer(&_positions[0], _positions.size() * sizeof(float));
		auto* layout = new BufferLayout();
		layout->push<float>(3); // Coords
		va->add_buffer(*vb, *layout);
		auto* ib = new IndexBuffer(indexes, 12 * 3);
		set_index_buffer(ib);
		set_vertex_array(va);
	}

	void fillWithoutIndexes()
	{
		_vertexes = 36;
		int index = 0;
		for (int i = 0; i < _vertexes * 3; i += 3) {
			_full_data.emplace_back(_positions[indexes[index] * 3]);
			_full_data.emplace_back(_positions[indexes[index] * 3 + 1]);
			_full_data.emplace_back(_positions[indexes[index] * 3 + 2]);
			index++;
		}
		auto* va = new VertexArray();
		auto* vb = new VertexBuffer(&_full_data[0], _full_data.size() * sizeof(float));
		auto* layout = new BufferLayout();
		layout->push<float>(3); // Coords
		va->add_buffer(*vb, *layout);
		set_vertex_array(va);
	}

	void set_position(const float positions[]) override {}
	void set_position(const glm::vec2 newBotLeft) override {}

	void add_data(const float* data, unsigned count) override
	{
		std::vector<float> fullData;
		//auto* fullData = new float[_vertexes * 3 + count];
		const int dataPerVertex = count / _vertexes;
		int index = 0, index2 = 0;
		for (int i = 0; i < _vertexes * 3 + count; i += (3 + dataPerVertex))
		{
			fullData.emplace_back(_full_data[index]);
			fullData.emplace_back(_full_data[index + 1]);
			fullData.emplace_back(_full_data[index + 2]);
			index += 3;
			for (int j = 0; j < dataPerVertex; j++)
			{
				fullData.emplace_back(data[index2]);
				index2++;
			}
		}
		for (int i = 1; i < ((_vertexes * 3) + count + 1); ++i)
		{
			std::cout << fullData[i - 1] << ", ";
			if (i % (3 + dataPerVertex) == 0)
			{
				std::cout << "\n";
			}
		}
		auto vb = new VertexBuffer(&fullData[0], fullData.size() * sizeof(float), _vertexes);
		BufferLayout* layout = new BufferLayout();
		layout->push<float>(3);
		layout->push<float>(dataPerVertex);
		vertex_array()->add_buffer(*vb, *layout);
	}
};
