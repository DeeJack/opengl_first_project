#include "TestClearColor.h"

#include <GLEW/glew.h>

#include "imgui/imgui.h"

namespace test
{
	TestClearColor::TestClearColor()
	{
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
	}

	void TestClearColor::on_imgui_render()
	{
		ImGui::ColorEdit4("Clear color", _color);
	}
}

