#pragma once
#include "Test.h"
#include "../renderer/Renderer.h"
#include "../textures/Texture.h"
#include "glm/gtx/transform.hpp"

namespace test
{
	class TestClearColor : public Test
	{
	private:
		float _color[4]{0.2F, 0.3F, 0.8F, 1.F};
		std::vector<Shape*> _shapes;
		Renderer _renderer;
		Shader _shader;
		const glm::mat4 _proj = glm::ortho(0.0F, 1280.0F, 0.0F, 720.0F, -500.0F, 500.0F);
		glm::mat4 _model = glm::mat4(1.0F);
		glm::mat4 _view = glm::translate(glm::mat4(1.0F), glm::vec3(0.0F, 0.0F, 0.0F));
		glm::vec3 _translation = glm::vec3(0, 0, 0);
		Texture t;
	public:
		TestClearColor();
		~TestClearColor() override;

		void on_update(float deltaTime) override;
		void on_render() override;
		void on_imgui_render() override;
	};
}
