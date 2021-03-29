#pragma once
#include <vector>

#include "../Test.h"
#include "../../renderer/Renderer.h"
#include "../../shapes/2d/Rectangle.h"
#include "glm/gtx/transform.hpp"

namespace test
{
	class SevenSegmentTest : public Test
	{
	private:
		struct Segment
		{
			Rectangle* seg;
			bool isVisible = true;
		};

		const unsigned int NUM_VALUES[10] = {0x7E, 0x30, 0x6D, 0x79, 0x33, 0x5B, 0x5F, 0x70, 0x7F, 0x7B};

		glm::mat4 _projection = glm::ortho(0, 1280, 720, 0, -500, 500);
		std::vector<Segment> _segments;
		Renderer _renderer;
		Shader _shader = Shader("res/shaders/Basic.shader");
		int _count = 0;

		void update_segments(unsigned int newValue);
	public:
		SevenSegmentTest();
		~SevenSegmentTest() override;

		void on_update(float deltaTime) override;
		void on_render() override;
		void on_imgui_render() override;
	};
}
