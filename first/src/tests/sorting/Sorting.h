#pragma once
#include "../Test.h"

namespace test
{
	class Sorting : public Test
	{
	public:
		Sorting();
		~Sorting();

		void on_update(float deltaTime) override;
		void on_render() override;
		void on_imgui_render() override;
	};
	
}
