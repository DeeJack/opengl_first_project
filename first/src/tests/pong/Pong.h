#pragma once
#include "../Test.h"
#include "../../renderer/Renderer.h"
#include "../../scenes/SevenSegment.h"
#include "../../shaders/Shader.h"
#include "../../shapes/2d/Circle.h"
#include "../../shapes/2d/Rectangle.h"
#include "glm/gtx/transform.hpp"

namespace test
{
	struct Ball
	{
		glm::vec3 position = glm::vec3(0.F);
		Circle* shape = nullptr;
		glm::mat4 model = glm::mat4(1.F);
		glm::vec2 speed = glm::vec2(150.F, 150.F);
	};

	struct Racket
	{
		Rectangle* shape = nullptr;
		glm::mat4 model = glm::mat4(1.F);
		glm::vec2 position;
	};

	class Pong : public Test
	{
	private:
		int WINDOW_WIDTH, WINDOW_HEIGHT;
		glm::mat4 _projection = glm::mat4(1.F);
		Shader _shader = Shader("res/shaders/Basic.shader");
		Renderer _renderer;
		glm::vec2 _center;
		Ball ball;
		Racket rackets[2];
		int scores[2] = {0, 0};
		SevenSegment _seven_segments[2] = {
			SevenSegment(glm::vec3(100.F, 100.F, 0.F), 0.3),
			SevenSegment(glm::vec3(900.F, 100.F, 0.F), 0.3)
		};

		void check_intersection();
	public:
		Pong();
		~Pong() override;
		void on_update(float deltaTime) override;
		void on_render() override;
		void on_imgui_render() override;
	};
}
