#pragma once
#include "../Test.h"
#include "../../renderer/Renderer.h"
#include "../../shaders/Shader.h"
#include "../../shapes/2d/Circle.h"
#include "glm/gtx/transform.hpp"

namespace test
{
	class Pong : public Test
	{
	private:
		int WINDOW_WIDTH, WINDOW_HEIGHT;
		float BALL_SPEED_X = 150.F;
		float BALL_SPEED_Y = 150.F;
		glm::mat4 _projection = glm::mat4(1.F);
		glm::mat4 _model = glm::mat4(1.F);
		Shader _shader = Shader("res/shaders/Basic.shader");
		Renderer _renderer;
		Circle* _circle;
		glm::vec3 _position;
	public:
		Pong();
		~Pong() override;
		void on_update(float deltaTime) override;
		void on_render() override;
		void on_imgui_render() override;
	};
}
