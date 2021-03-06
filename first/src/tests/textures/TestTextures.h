#pragma once

#include "../Test.h"
#include "../../renderer/Renderer.h"
#include "../../shapes/2d/Circle.h"
#include "../../shapes/2d/Rectangle.h"
#include "../../textures/Texture.h"
#include "../shapes/Shape.h"
#include "glm/gtx/transform.hpp"

namespace test
{
	class TestTextures : public Test
	{
	private:
		Shader _shader;
		Renderer _renderer;
		Circle* _circle = nullptr;
		Rectangle* _box = nullptr;
		const glm::mat4 _proj = glm::ortho(0.0F, 1280.0F, 0.0F, 720.0F, -100.0F, 100.0F);
		glm::mat4 _view = glm::translate(glm::mat4(1.0F), glm::vec3(0.0F, 0.0F, 0.0F));
		glm::vec3 _translation = glm::vec3(0, 0, 0);
		Texture _texture;
	public:
		TestTextures();
		~TestTextures() override;

		void init();

		void on_update(float deltaTime) override;
		void on_render() override;
		void on_imgui_render() override;
	};
}
