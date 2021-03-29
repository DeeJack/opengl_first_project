#include "Pong.h"

#include "../../util.h"
#include "imgui/imgui.h"

namespace test
{
	Pong::Pong()
	{
		_shader.bind();
		get_window_size(&WINDOW_WIDTH, &WINDOW_HEIGHT);

		_projection = glm::ortho(0.F, static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT),
		                         0.F, -500.F, 500.F);

		const glm::vec2 center(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
		_circle = new Circle(center, 50);
		_position = glm::vec3(center, 0.F);
		_shader.set_uniform4f("u_color", 1.F, 1.F, 1.F, 1.F);
	}

	Pong::~Pong()
	{
		delete _circle;
	}

	void Pong::on_update(float deltaTime)
	{
		const auto changeX = (BALL_SPEED_X * deltaTime);
		const auto changeY = (BALL_SPEED_Y * deltaTime);

		const glm::vec3 translation = glm::vec3(changeX, changeY, 0.F);
		_position.x += translation.x;
		_position.y += translation.y;
		if (_position.x > WINDOW_WIDTH && BALL_SPEED_X > 0)
			BALL_SPEED_X = -BALL_SPEED_X;
		else if (_position.x < 0 && BALL_SPEED_X < 0)
			BALL_SPEED_X = -BALL_SPEED_X;
		if (_position.y > WINDOW_HEIGHT && BALL_SPEED_Y > 0)
			BALL_SPEED_Y = -BALL_SPEED_Y;
		else if (_position.y < 0 && BALL_SPEED_Y < 0)
			BALL_SPEED_Y = -BALL_SPEED_Y;
		_model = glm::translate(_model, translation);
	}

	void Pong::on_render()
	{
		const auto mvp = _projection * _model;
		_shader.set_uniform_mat4f("u_mvp", mvp);
		_renderer.draw(*_circle, _shader);
	}

	void Pong::on_imgui_render()
	{
		ImGui::Begin("Options");
		ImGui::SliderFloat("Speed x: ", &BALL_SPEED_X, 0, 4000);
		ImGui::SliderFloat("Speed y: ", &BALL_SPEED_Y, 0, 4000);
		ImGui::End();
	}
}
