#pragma once
#include "Test.h"

namespace test
{
	class TestClearColor : public Test
	{
	private:
		float _color[4]{1.F, 1.F, 1.F, 1.F};
	public:
		TestClearColor();
		~TestClearColor();
		
		void on_update(float deltaTime) override;
		void on_render() override;
		void on_imgui_render() override;
	};
}