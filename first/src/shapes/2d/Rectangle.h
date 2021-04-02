#pragma once
#include "../Shape.h"
#include "glm/vec2.hpp"

class Rectangle : public Shape
{
private:
	float _width;
	float _height;
	glm::vec2 _botLeft;
	std::vector<float> _positions;
public:
	Rectangle(const glm::vec2& botLeft, const glm::vec2& topRight)
		: Shape(DrawType::INDICES), _width(topRight.x - botLeft.x), _height(topRight.y - botLeft.y), _botLeft(botLeft)
	{
		_positions = {
			botLeft.x, botLeft.y,
			topRight.x, botLeft.y,
			topRight.x, topRight.y,
			botLeft.x, topRight.y
		};
		auto* va = new VertexArray();
		auto* vb = new VertexBuffer(&_positions[0], 4 * 2 * sizeof(float));
		auto* layout = new BufferLayout();
		layout->push<float>(2);
		va->add_buffer(*vb, *layout);
		const unsigned int indexes[] = { 0, 1, 2, 0, 2, 3 };
		auto* ib = new IndexBuffer(indexes, 6);
		set_index_buffer(ib);
		set_vertex_array(va);
	}
	
	Rectangle(const glm::vec2& botLeft, float width, float height) :
		Rectangle(botLeft, glm::vec2(botLeft.x + width, botLeft.y + height))
	{
	}

	void set_position(const glm::vec2 newBotLeft) override
	{
		_botLeft = newBotLeft;
		_positions.clear();
		_positions = {
			newBotLeft.x, newBotLeft.y,
			newBotLeft.x + _width, newBotLeft.y,
			newBotLeft.x + _width, newBotLeft.y + _height,
			newBotLeft.x, newBotLeft.y + _height
		};
		vertex_array()->bind();
		vertex_array()->bound_buffer()->bind();
		vertex_array()->bound_buffer()->change_data(&_positions[0], 4 * 2 * sizeof(float));
	}

	void set_position(const float positions[8]) override
	{
		_positions.clear();
		for (int i = 0; i != 8; ++i)
			_positions.emplace_back(positions[i]);
		vertex_array()->bind();
		vertex_array()->bound_buffer()->bind();
		vertex_array()->bound_buffer()->change_data(positions, 4 * 2 * sizeof(float));
	}

	void add_data(const float* data, unsigned count) override
	{
		//float* fullData = new float[8 + count];
		std::vector<float> fullData;
		int index = 0;
		for (int i = 0; i != 8 + count; i += 4)
		{
			fullData.emplace_back(_positions[index]);
			fullData.emplace_back(_positions[index + 1]);
			fullData.emplace_back(data[index]);
			fullData.emplace_back(data[index + 1]);
			index += 2;
		}
		VertexBuffer::unbind();
		delete vertex_array()->bound_buffer();
		auto* vb = new VertexBuffer(&fullData[0], 4 * 4 * sizeof(float));
		auto* layout = new BufferLayout();
		layout->push<float>(2);
		layout->push<float>(2);
		vertex_array()->add_buffer(*vb, *layout);
	}

	bool intersect(const glm::vec2& point) override
	{
		static const int offset = 3;
		return (point.y > _botLeft.y && point.y < (_botLeft.y + _height) &&
			((point.x > _botLeft.x - offset) && (point.x < _botLeft.x + _width + offset)));
	}
	
	bool intersect(const Shape& otherShape) override
	{
		return false;
	}


	float width() const;
	float height() const;
	glm::vec2 bot_left() const;
};

inline float Rectangle::width() const
{
	return _width;
}

inline float Rectangle::height() const
{
	return _height;
}

inline glm::vec2 Rectangle::bot_left() const
{
	return _botLeft;
}
