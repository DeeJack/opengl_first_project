#pragma once
#include "../Shape.h"
#include "glm/vec2.hpp"

class Rectangle : public Shape
{
private:
	float _width;
	float _height;
	glm::vec2 _botLeft;
public:
	Rectangle(const glm::vec2& botLeft, const glm::vec2& topRight, Shader* shader) : Shape()
	{
		const float positions[] = {
			botLeft.x, botLeft.y,
			topRight.x, botLeft.y,
			topRight.x, topRight.y,
			botLeft.x, topRight.y
		};
		_width = topRight.x - botLeft.x;
		_height = topRight.y - botLeft.y;
		_botLeft = botLeft;
		auto va = new VertexArray();
		auto vb = new VertexBuffer(positions, 4 * 2 * sizeof(float));
		BufferLayout layout;
		layout.push<float>(2);
		va->add_buffer(*vb, layout);
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
		float positions[] = {
			newBotLeft.x, newBotLeft.y,
			newBotLeft.x + _width, newBotLeft.y,
			newBotLeft.x + _width, newBotLeft.y + _height,
			newBotLeft.x, newBotLeft.y + _height
		};
		vertex_array()->bind();
		vertex_array()->bound_buffer()->bind();
		vertex_array()->bound_buffer()->set_data(positions, 4 * 2 * sizeof(float));
	}

	void set_position(const float positions[8]) override
	{
		vertex_array()->bind();
		vertex_array()->bound_buffer()->bind();
		vertex_array()->bound_buffer()->set_data(positions, 4 * 2 * sizeof(float));
	}
};
