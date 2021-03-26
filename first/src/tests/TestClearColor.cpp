#include "TestClearColor.h"

#include <GLEW/glew.h>


#include "../shapes/2d/polygon/Pentagon.h"
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
		_shapes.emplace_back(new Pentagon(vertexes, &_shader));
		
	}

	TestClearColor::~TestClearColor()
	{
	}

	void TestClearColor::on_update(float deltaTime)
	{

	}

	void TestClearColor::on_render()
	{
		glClearColor(_color[0], _color[1], _color[2], _color[3]);
		glClear(GL_COLOR_BUFFER_BIT);
		_shader.bind();
		glm::mat4 model = glm::translate(glm::mat4(1.0F), translation);
		glm::mat4 mvp = proj * view * model;
		_shader.set_uniform_mat4f("u_mvp", mvp);
		for (const auto shape : _shapes)
			renderer.drawNoColor(*shape);
	}

	void TestClearColor::on_imgui_render()
	{
		ImGui::Begin("Background color");
		ImGui::ColorEdit4("Clear color", _color);
		ImGui::SliderFloat3("Translation", &translation.x, -100.0F, 500.0F);
		ImGui::End();
	}
}

