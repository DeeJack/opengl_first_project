#include "SevenSegment.h"

#include <algorithm>
#include <stdexcept>

struct TempSegment
{
	glm::vec2 pos;
	bool horizontal;
};

SevenSegment::SevenSegment(const glm::vec3 startPosition, float scale)
	: _start_position(startPosition), _scale(scale)
{
	init();
}

SevenSegment::SevenSegment(const SevenSegment& other)
	: _start_position(other._start_position), _scale(other._scale)
{
	*this = other;
}

void SevenSegment::init()
{
	const float offset = 10 * _scale;
	const TempSegment pos[] = {
			{glm::vec2(_start_position.x, _start_position.y), true}, // A
			{glm::vec2(_start_position.x + offset * 11, _start_position.y + offset * 3), false}, // B
			{glm::vec2(_start_position.x + offset * 11, _start_position.y + offset * 14), false}, // C
			{glm::vec2(_start_position.x, _start_position.y + offset * 24), true}, // D
			{glm::vec2(_start_position.x - offset * 3, _start_position.y + offset * 14), false}, // E
			{glm::vec2(_start_position.x - offset * 3, _start_position.y + offset * 3), false}, // F
			{glm::vec2(_start_position.x, _start_position.y + offset * 13), true}, // G
	};
	for (const auto& x : pos)
	{
		float width = x.horizontal ? 100 : 20;
		float height = x.horizontal ? 20 : 100;
		_segments.push_back({ new Rectangle(x.pos, width * _scale, height * _scale) });
	}
}

SevenSegment::~SevenSegment()
{
	for (const auto& x : _segments)
		delete x.seg;
}

std::vector<SevenSegment::Segment> SevenSegment::get_segments() const
{
	return _segments;
}

void SevenSegment::update_segments(unsigned int newValue)
{
	// Each bit represent a segment,
	// For example, 256 : 10000000 -> every bit is off
	// 126 (0x7E) -> 1111110 -> Every bit on aside from the last one (G) -> 0
	int shiftIndex = 6;
	for (int i = 0; i != 7; ++i)
	{
		if ((newValue >> shiftIndex) & 1)
			_segments[i].isVisible = true;
		else
			_segments[i].isVisible = false;
		--shiftIndex;
	}
}

void SevenSegment::show(const int value)
{
	if (value < 0 || value > 9)
		throw std::invalid_argument("Seven segment display can only show numbers from 0 to 9");
	update_segments(NUM_VALUES[value]);
}

void SevenSegment::set_color(const glm::vec4& colors)
{
	_colors = colors;
	for (const auto& x : _segments)
		x.seg->set_color(colors);
}

SevenSegment& SevenSegment::operator=(const SevenSegment& other)
{
	_start_position = other._start_position;
	_scale = other._scale;
	_segments.clear();
	_segments.shrink_to_fit();
	init();
	set_color(other._colors);
	return *this;
}
