#pragma once
#include <vector>

#include "../Test.h"
#include "../../renderer/Renderer.h"
#include "../../scenes/SevenSegment.h"
#include "../../shapes/2d/Rectangle.h"
#include "glm/gtx/transform.hpp"

namespace test
{
	class SevenSegmentTest : public Test
	{
	private:
		glm::mat4 _projection = glm::ortho(0.F, 1280.F, 720.F, 0.F, -500.F, 500.F);
		Renderer _renderer;
		Shader _shader = Shader("res/shaders/textures.shader");
		int _count = 0;
		SevenSegment _seven_segments[2] = {
			{glm::vec3(100, 100, 0), 1.0},
			{glm::vec3(285, 100, 0), 1.0},
		};
	public:
		SevenSegmentTest();
		~SevenSegmentTest() override;

		void on_update(float deltaTime) override;
		void on_render() override;
		void on_imgui_render() override;
	};
}
