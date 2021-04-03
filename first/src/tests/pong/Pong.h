#pragma once

#include "../Test.h"
#include "../../renderer/Renderer.h"
#include "../../scenes/SevenSegment.h"
#include "../../shaders/Shader.h"
#include "../../shapes/2d/Circle.h"
#include "../../shapes/2d/Rectangle.h"
#include "glm/gtx/transform.hpp"
#include "imgui/imgui_impl_glfw.h"

namespace test
{
	struct Ball
	{
		glm::vec3 position = glm::vec3(0.F);
		Circle* shape = nullptr;
		glm::mat4 model = glm::mat4(1.F);
		glm::vec2 speed = glm::vec2(1500.F, 150.F);
	};

	struct Racket
	{
		Rectangle* shape = nullptr;
		glm::mat4 model = glm::mat4(1.F);
		glm::vec2 position = glm::vec2(0.F);
	};

	class Pong : public Test
	{
	private:
		int WINDOW_WIDTH = 0, WINDOW_HEIGHT = 0;
		glm::mat4 _projection = glm::mat4(1.F);
		Shader _shader = Shader("res/shaders/Basic.shader");
		Renderer _renderer;
		glm::vec2 _center = glm::vec2(0.F);
		Ball ball;
		Racket rackets[2];
		int scores[2] = {0, 0};
		SevenSegment _seven_segments[2] = {
			{glm::vec3(550.F, 45.F, 0.F), 0.3F},
			{glm::vec3(700.F, 45.F, 0.F), 0.3F}
		};
		bool finished = false;
		
		void check_intersection();
		void init();
	public:
		void on_resize(const GLFWwindow* window, const int width, const int height);
		Pong();
		~Pong() override;
		void finish();
		void on_update(float deltaTime) override;
		void on_render() override;
		void on_imgui_render() override;
	};
}
