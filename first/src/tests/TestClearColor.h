#pragma once
#include "Test.h"
#include "../renderer/Renderer.h"
#include "glm/gtx/transform.hpp"

namespace test
{
	class TestClearColor : public Test
	{
	private:
		float _color[4]{0.2F, 0.3F, 0.8F, 1.F};
		Renderer renderer;
		std::vector<Shape*> _shapes;
		Shader _shader;
		const glm::mat4 proj = glm::ortho(0.0F, 1280.0F, 0.0F, 720.0F, -100.0F, 100.0F);
		glm::mat4 view = glm::translate(glm::mat4(1.0F), glm::vec3(0.0F, 0.0F, 0.0F));
		glm::vec3 translation = glm::vec3(0, 0, 0);
	public:
		TestClearColor();
		~TestClearColor();
		
		void on_update(float deltaTime) override;
		void on_render() override;
		void on_imgui_render() override;
	};
}
