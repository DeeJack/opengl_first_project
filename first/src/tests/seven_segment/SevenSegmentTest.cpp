#include "SevenSegmentTest.h"

#include <GLFW/glfw3.h>


#include "../../shapes/2d/Rectangle.h"

namespace test
{
	struct TempSegment
	{
		glm::vec2 pos;
		bool horizontal;
	};

	void SevenSegmentTest::update_segments(unsigned int newValue)
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

	SevenSegmentTest::SevenSegmentTest()
		: _shader("res/shaders/basic.shader")
	{
		_shader.bind();
		_projection = glm::ortho(0.F, 1280.F, 720.F, 0.F, -500.F, 500.F);
		const TempSegment pos[] = {
			{glm::vec2(100, 100), true}, // A
			{glm::vec2(210, 120), false}, // B
			{glm::vec2(210, 230), false}, // C
			{glm::vec2(100, 320), true}, // D
			{glm::vec2(70, 230), false}, // E
			{glm::vec2(70, 120), false}, // F
			{glm::vec2(100, 210), true}, // G
		};
		for (const auto& x : pos)
		{
			int width = x.horizontal ? 100 : 20;
			int height = x.horizontal ? 20 : 100;
			_segments.push_back({ new Rectangle(x.pos, width, height) });
		}
		glfwSwapInterval(60);
	}

	SevenSegmentTest::~SevenSegmentTest()
	{
		for (const auto& x : _segments)
		{
			delete x.seg;
		}
		glfwSwapInterval(1);
	}

	void SevenSegmentTest::on_update(float deltaTime)
	{
		update_segments(NUM_VALUES[_count]);
		_count = (_count + 1) % 10;
	}

	void SevenSegmentTest::on_render()
	{
		for (const auto& x : _segments)
		{
			if (x.isVisible)
				_renderer.draw(*x.seg, _shader);
			else
				_renderer.draw_no_color(*x.seg, _shader);
		}
	}

	void SevenSegmentTest::on_imgui_render()
	{
	}
}
