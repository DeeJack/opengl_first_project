#pragma once

namespace test
{
	class Test
	{
	public:
		Test() = default;

		~Test() = default;

		virtual void on_update(float deltaTime) = 0;
		virtual void on_render() = 0;
		virtual void on_imgui_render() = 0;
	};
}