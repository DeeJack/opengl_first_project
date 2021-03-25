#pragma once
#include "../Shape.h"

class CubeTest : public Shape
{
private:
	float* _positions;
	float* _full_data;
	int _vertexes;
	char* _letters;
public:
	CubeTest(glm::vec3 first, glm::vec3 second, Shader* shader)
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
			4, 5, 6, // EFG
			5, 7, 6, // FHG
			6, 0, 7, // GAH
			0, 3, 7, // ADH
			2, 5, 3, // CFD
			5, 7, 3, // FHD
			0, 1, 6, //ABG
			1, 4, 6 // BEG
		};
		_vertexes = 36;
		_full_data = new float[_vertexes * 3];
		_letters = new char[36];
		int index = 0;
		for (int i = 0; i < _vertexes * 3; i += 3) {
			_full_data[i + 0] = _positions[indexes[index] * 3];
			_full_data[i + 1] = _positions[indexes[index] * 3 + 1];
			_full_data[i + 2] = _positions[indexes[index] * 3 + 2];
			_letters[index] = static_cast<char>('A' + indexes[index]);
			index++;
		}
		std::cout << "Full data (positions): \n0: ";
		for (int i = 1; i < ((_vertexes * 3) + 1); ++i)
		{
			std::cout << _full_data[i - 1] << ", ";
			if (i % 3 == 0)
				std::cout << "\n" << i << ": ";
		}
		auto* va = new VertexArray();
		auto* vb = new VertexBuffer(_full_data, (_vertexes * 3) * sizeof(float));
		auto* layout = new BufferLayout();
		layout->push<float>(3); // Coords
		va->add_buffer(*vb, *layout);
		//IndexBuffer* ib = new IndexBuffer(indexes, 12 * 3);
		//set_index_buffer(ib);
		set_vertex_array(va);
		set_shader(shader);
	}

	void set_position(const float positions[]) override {}
	void set_position(const glm::vec2 newBotLeft) override {}
	void add_data(const float* data, unsigned count) override
	{
		float* fullData = new float[_vertexes * 3 + count];
		int dataPerVertex = count / _vertexes;
		int index = 0, index2 = 0;
		for (int i = 0; i < _vertexes * 3 + count; i += (3 + dataPerVertex))
		{
			fullData[i] = _full_data[index];
			fullData[i + 1] = _full_data[index + 1];
			fullData[i + 2] = _full_data[index + 2];
			index += 3;
			for (int j = 0; j < dataPerVertex; j++)
			{
				fullData[i + 3 + j] = data[index2];
				index2++;
			}
		}
		int lettersCount = 0;
		for (int i = 1; i < ((_vertexes * 3) + count + 1); ++i)
		{
			std::cout << fullData[i - 1] << ", ";
			if (i % (3 + dataPerVertex) == 0)
			{
				std::cout << "(" << _letters[lettersCount] << ")";
				lettersCount++;
				std::cout << "\n";
			}
		}
		vertex_array()->bound_buffer()->unbind();
		delete vertex_array()->bound_buffer();
		auto vb = new VertexBuffer(fullData, (_vertexes * (3 + dataPerVertex)) * sizeof(float), _vertexes);
		BufferLayout* layout = new BufferLayout();
		layout->push<float>(3);
		layout->push<float>(dataPerVertex);
		vertex_array()->add_buffer(*vb, *layout);
	}
};
