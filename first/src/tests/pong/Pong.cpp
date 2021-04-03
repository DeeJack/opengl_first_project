#include "Pong.h"

#include "../../util.h"
#include "imgui/imgui.h"

namespace test
{
	static Pong* PONG_INSTANCE = nullptr;
	void Pong::on_resize(const GLFWwindow* window, const int width, const int height)
	{
		WINDOW_WIDTH = width;
		WINDOW_HEIGHT = height;
		glViewport(0, 0, width, height);
		delete rackets[0].shape;
		delete rackets[1].shape;
		delete ball.shape;
		ball.model = glm::mat4(1.F);
		rackets[0].model = glm::mat4(1.F);
		rackets[1].model = glm::mat4(1.F);
		init();
		_seven_segments[0].show(scores[0]);
		_seven_segments[1].show(scores[1]);
	}

	void Pong::init()
	{
		log(std::to_string(WINDOW_WIDTH) + " - " + std::to_string(WINDOW_HEIGHT));
		_projection = glm::ortho(0.F, static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT),
			0.F, -500.F, 500.F);

		_center = glm::vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
		ball.shape = new Circle(_center, 20);
		ball.position = glm::vec3(_center, 0.F);
		_shader.set_uniform4f("u_color", 1.F, 1.F, 1.F, 1.F);
		const glm::vec2 firstRacketPoint(20, 10);
		rackets[0].shape = new Rectangle(firstRacketPoint, 20.F, 100.F);
		rackets[0].shape->set_color(glm::vec4(0.F, 255.F, 0.F, 1.F));
		rackets[0].position = firstRacketPoint;
		const glm::vec2 secondRacketPoint(WINDOW_WIDTH - 35, 10);
		rackets[1].position = secondRacketPoint;
		rackets[1].shape = new Rectangle(secondRacketPoint, 20.F, 100.F);
		rackets[1].shape->set_color(glm::vec4(255.F, 0.F, 0.F, 1.F));
		
		_seven_segments[0] = SevenSegment{ glm::vec3(WINDOW_WIDTH / 2 - 100, 45.F, 0.F), 0.3F };
		_seven_segments[1] = SevenSegment{ glm::vec3(WINDOW_WIDTH / 2 + 100, 45.F, 0.F), 0.3F };
		_seven_segments[0].set_color(glm::vec4(0.F, 255.F, 0.F, 1.F));
		_seven_segments[1].set_color(glm::vec4(255.F, 0.F, 0.F, 1.F));
	}
	
	Pong::Pong()
	{
		PONG_INSTANCE = this;
		glfwSwapInterval(0);
		_shader.bind();
		get_window_size(&WINDOW_WIDTH, &WINDOW_HEIGHT);
		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

		init();
		
		_seven_segments[0].show(0);
		_seven_segments[1].show(0);
		auto* window = current_window();
		glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height)
		{
			if(PONG_INSTANCE != nullptr)
				PONG_INSTANCE->on_resize(window, width, height);
		});
	}

	Pong::~Pong()
	{
		PONG_INSTANCE = nullptr;
		delete ball.shape;
		for (const auto& racket : rackets)
			delete racket.shape;
		auto* window = current_window();
		glfwSetFramebufferSizeCallback(window, nullptr);
	}


	void Pong::check_intersection()
	{
		static Racket* lastHit = nullptr;
		auto* racket = &rackets[0];
		if (ball.position.x > WINDOW_WIDTH / 2)
			racket = &racket[1];
		auto intersect = false;
		const auto radius = static_cast<double>(ball.shape->radius());
		for (int i = 0; i < 360; i += 30) // 30 degrees angles until 360 (full circle)
		{
			const auto x = radius * cos(static_cast<double>(i)) + ball.position.x;
			const auto y = radius * sin(static_cast<double>(i)) + ball.position.y;

			static const int offset = 3;
			intersect = (y > racket->position.y - offset && 
				y < (racket->position.y + racket->shape->height() + offset) &&
				((x > racket->position.x - offset) &&
				(x < racket->position.x + racket->shape->width() + offset)));
			if (intersect)
				break;
		}
		if (intersect && lastHit != racket)
		{
			lastHit = racket;
			ball.speed.x = -ball.speed.x;
		}
	}

	void Pong::on_update(float deltaTime)
	{
		if (finished)
			return;
		const auto changeX = (ball.speed.x * deltaTime);
		const auto changeY = (ball.speed.y * deltaTime);
		const auto radius = ball.shape->radius();

		const auto translation = glm::vec3(changeX, changeY, 0.F);
		ball.position.x += translation.x;
		ball.position.y += translation.y;
		if (ball.position.x + radius > static_cast<float>(WINDOW_WIDTH) && ball.speed.x > 0)
		{
			scores[0]++;
			ball.speed.x = -ball.speed.x;
			ball.position = glm::vec3(_center, 0.F);
			ball.model = glm::mat4(1.F);
			return;
		}
		if (ball.position.x - radius < 0 && ball.speed.x < 0)
		{
			scores[1]++;
			ball.speed.x = -ball.speed.x;
			ball.position = glm::vec3(_center, 0.F);
			ball.model = glm::mat4(1.F);
			return;
		}
		if (ball.position.y + radius > static_cast<float>(WINDOW_HEIGHT) && ball.speed.y > 0)
			ball.speed.y = -ball.speed.y;
		else if (ball.position.y - radius < 0 && ball.speed.y < 0)
			ball.speed.y = -ball.speed.y;
		ball.model = glm::translate(ball.model, translation);

		double mousePosY, mousePosX;

		get_mouse_position(&mousePosX, &mousePosY);
		if (mousePosY > WINDOW_HEIGHT - 100)
			mousePosY = WINDOW_HEIGHT - 100;
		else if (mousePosY < 0)
			mousePosY = 0;
		auto* currentPlayer = &rackets[0];
		if (mousePosX > WINDOW_WIDTH / 2)
			currentPlayer = &rackets[1];
		currentPlayer->position.y = static_cast<float>(mousePosY);
		currentPlayer->model = glm::translate(glm::mat4(1.F), glm::vec3(0.F, mousePosY, 0.F));
		check_intersection();
		_seven_segments[0].show(scores[0]);
		_seven_segments[1].show(scores[1]);
		if (scores[0] == 9 || scores[1] == 9)
			finish();
	}

	void Pong::finish()
	{
		finished = true;
		ball.speed.x = 0;
		ball.speed.y = 0;
	}

	void Pong::on_render()
	{
		const auto ball_mvp = _projection * ball.model;
		_shader.set_uniform_mat4f("u_mvp", ball_mvp);
		_renderer.draw(*ball.shape, _shader);

		const auto racket_1_mvp = _projection * rackets[0].model;
		_shader.set_uniform_mat4f("u_mvp", racket_1_mvp);
		_renderer.draw(*rackets[0].shape, _shader);
		const auto racket_2_mvp = _projection * rackets[1].model;
		_shader.set_uniform_mat4f("u_mvp", racket_2_mvp);
		_renderer.draw(*rackets[1].shape, _shader);
		_shader.set_uniform_mat4f("u_mvp", _projection);

		for (int i = 0; i != 2; ++i)
		{
			for (const auto &x : _seven_segments[i].get_segments())
				if (x.isVisible)
					_renderer.draw(*(x.seg), _shader);
		}
	}

	void Pong::on_imgui_render()
	{
		ImGui::Begin("Options");
		ImGui::SliderFloat("Speed x: ", &ball.speed.x, 0, 4000);
		ImGui::SliderFloat("Speed y: ", &ball.speed.y, 0, 4000);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0F / ImGui::GetIO().Framerate,
		            ImGui::GetIO().Framerate);
		ImGui::Text("Scores: %d-%d", scores[0], scores[1]);
		ImGui::End();
	}
}
