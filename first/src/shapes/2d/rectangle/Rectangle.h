#pragma once
#include "../../Shape.h"
#include "glm/vec2.hpp"

class Rectangle : public Shape
{
private:
	float _width;
	float _height;
	glm::vec2 _botLeft;
	float* _positions;
public:
	Rectangle(const glm::vec2& botLeft, const glm::vec2& topRight, Shader* shader) : Shape()
	{
		_positions = new float[] {
			botLeft.x, botLeft.y,
			topRight.x, botLeft.y,
			topRight.x, topRight.y,
			botLeft.x, topRight.y
		};
		_width = topRight.x - botLeft.x;
		_height = topRight.y - botLeft.y;
		_botLeft = botLeft;
		auto va = new VertexArray();
		auto vb = new VertexBuffer(_positions, 4 * 2 * sizeof(float));
		BufferLayout* layout = new BufferLayout();
		layout->push<float>(2);
		va->add_buffer(*vb, *layout);
		const unsigned int indexes[] = { 0, 1, 2, 0, 2, 3 };
		IndexBuffer* ib = new IndexBuffer(indexes, 6);
		set_index_buffer(ib);
		set_vertex_array(va);
		set_shader(shader);
	}
	
	Rectangle(const glm::vec2& botLeft, float width, float height, Shader* shader) :
		Rectangle(botLeft, glm::vec2(botLeft.x + width, botLeft.y + height), shader)
	{
	}

	void set_position(const glm::vec2 newBotLeft) override
	{
		_botLeft = newBotLeft;
		delete _positions;
		_positions = new float[] {
			newBotLeft.x, newBotLeft.y,
			newBotLeft.x + _width, newBotLeft.y,
			newBotLeft.x + _width, newBotLeft.y + _height,
			newBotLeft.x, newBotLeft.y + _height
		};
		vertex_array()->bind();
		vertex_array()->bound_buffer()->bind();
		vertex_array()->bound_buffer()->set_data(_positions, 4 * 2 * sizeof(float));
	}

	void set_position(const float positions[8]) override
	{
		delete _positions;
		_positions = new float[8];
		for (int i = 0; i != 8; ++i)
			_positions[i] = positions[i];
		vertex_array()->bind();
		vertex_array()->bound_buffer()->bind();
		vertex_array()->bound_buffer()->set_data(positions, 4 * 2 * sizeof(float));
	}

	void add_data(const float* data, unsigned count) override
	{
		float* fullData = new float[8 + count];
		int index = 0;
		for (int i = 0; i != 8 + count; i += 4)
		{
			fullData[i] = _positions[index];
			fullData[i + 1] = _positions[index + 1];
			fullData[i + 2] = data[index];
			fullData[i + 3] = data[index + 1];
			index += 2;
		}
		for (int i = 1; i != 8 + count + 1; ++i)
		{
			std::cout << fullData[i - 1] << ", ";
			if (i % 4 == 0)
				std::cout << "\n";
		}
		vertex_array()->bound_buffer()->unbind();
		delete vertex_array()->bound_buffer();
		auto vb = new VertexBuffer(fullData, 4 * 4 * sizeof(float));
		BufferLayout* layout = new BufferLayout();
		layout->push<float>(2);
		layout->push<float>(2);
		vertex_array()->add_buffer(*vb, *layout);
		return;
		
		vertex_array()->bind();
		vertex_array()->bound_buffer()->bind();
		// TODO si faceva così o con attrib???
		vertex_array()->bound_buffer()->set_data(fullData, (8 + count) * sizeof(float));
		vertex_array()->bound_layout()->push<float>(2);
		vertex_array()->add_buffer(*vertex_array()->bound_buffer(), *vertex_array()->bound_layout());
	}
};
