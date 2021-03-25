#pragma once
#include "Test.h"

namespace test
{
	class TestClearColor : public Test
	{
	private:
		float _color[4]{0.2F, 0.3F, 0.8F, 1.F};
	public:
		TestClearColor();
		~TestClearColor();
		
		void on_update(float deltaTime) override;
		void on_render() override;
		void on_imgui_render() override;
	};
}