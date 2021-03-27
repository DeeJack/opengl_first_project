#include "TestClearColor.h"

#include <GLEW/glew.h>



#include "../shapes/2d/Circle.h"
#include "../shapes/2d/polygon/Pentagon.h"
#include "../shapes/2d/polygon/Polygon.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/gtx/transform.hpp"
#include "imgui/imgui.h"

namespace test
{
	TestClearColor::TestClearColor()
		: _shader("res/shaders/Basic.shader")
	{
		glm::vec2 vertexes[] = {
			{100.0F, 100.0F},
			{70.0F, 70.0F},
			{85.0F, 40.0F},
			{115.0F, 40.0F},
			{130.0F, 70.0F}
		};
		//_shapes.emplace_back(new Pentagon(vertexes, &_shader));
		//_shapes.emplace_back(new Circle(glm::vec2(400.F, 400.F), 30.F, &_shader));


		std::vector<glm::vec2> pos = {
			{700, 500},
			{900, 500},
			{950, 450},
			{900, 400},
			{700, 400},
			{650, 450},
		};
		
		_shapes.emplace_back(new Polygon(pos));
	}

	TestClearColor::~TestClearColor()
	{
	}

	void TestClearColor::on_update(float deltaTime)
	{
		//const float ROTATION_SPEED = 5.0F;
		//model = glm::translate(model, glm::vec3(0.F));
		//model = glm::rotate(model, ROTATION_SPEED * deltaTime, glm::vec3(-10.F, 0.F, 0.F));
		//model = glm::rotate(model, glm::radians(0.0F), glm::vec3(0.F, 1.F, 0.F));
		//model = glm::rotate(model, glm::radians(0.0F), glm::vec3(0.F, 1.F, 1.F));
		//model = glm::scale(model, glm::vec3(1.5F));
	}

	void TestClearColor::on_render()
	{
		glClearColor(_color[0], _color[1], _color[2], _color[3]);
		glClear(GL_COLOR_BUFFER_BIT);
		_shader.bind();
		glm::mat4 mvp = proj * model;
		_shader.set_uniform_mat4f("u_mvp", mvp);
		///for (const auto shape : _shapes)
		//renderer.draw_without_indexes_triangle_fan(*(_shapes[0]));
		renderer.draw(*(_shapes[0]), _shader);
	}

	void TestClearColor::on_imgui_render()
	{
		ImGui::Begin("Background color");
		ImGui::ColorEdit4("Clear color", _color);
		ImGui::SliderFloat3("Translation", &translation.x, -100.0F, 500.0F);
		ImGui::End();
	}
}

