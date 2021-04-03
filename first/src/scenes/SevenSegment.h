#pragma once
#include "../renderer/Renderer.h"
#include "../shapes/2d/Rectangle.h"
#include "glm/ext/matrix_clip_space.hpp"

class SevenSegment
{
private:
	struct Segment
	{
		Rectangle* seg;
		bool isVisible = true;
	};
	const unsigned int NUM_VALUES[10] = { 0x7E, 0x30, 0x6D, 0x79, 0x33, 0x5B, 0x5F, 0x70, 0x7F, 0x7B };

	//glm::mat4 _projection = glm::ortho(0, 1280, 720, 0, -500, 500);
	std::vector<Segment> _segments;
	glm::vec3 _start_position;
	float _scale;
	glm::vec4 _colors = glm::vec4(1.F);
	//Renderer _renderer;

public:
	SevenSegment(const glm::vec3 startPosition, float scale);
	SevenSegment(const SevenSegment& other);
	void init();

	~SevenSegment();

	std::vector<Segment> get_segments() const;
	void update_segments(unsigned newValue);
	void show(const int value);
	void set_color(const glm::vec4&);

	SevenSegment& operator=(const SevenSegment& other);
	
	//void scale(const float scale);
};
