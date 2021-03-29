#pragma once
#include "../Test.h"
#include "../../renderer/Renderer.h"
#include "../../shaders/Shader.h"
#include "../../shapes/2d/Rectangle.h"
#include "../../shapes/3d/Cube.h"
#include "../../shapes/3d/Pyramid.h"
#include "glm/fwd.hpp"
#include "glm/vec3.hpp"
#include "glm/gtx/transform.hpp"

namespace test
{
	class StaticMovement3d : public Test
	{
	private:
		Pyramid* _pyramid;
		glm::mat4 _view = glm::mat4(1.0F);
		glm::mat4 _proj = glm::mat4(1.0F);
		glm::mat4 _model = glm::mat4(1.0F);
		Shader _shader{"res/shaders/basic3d.shader"};
		Cube _cube{glm::vec3(300, 100, 100), glm::vec3(500, 300, 300)};
		Renderer _renderer;
		Rectangle* _rectangle;
		glm::vec3 _translation;
		glm::vec3 _last_translation;
	public:
		StaticMovement3d();
		~StaticMovement3d() override;

		void compute_mouse_movement(float deltaTime);
		void on_update(float deltaTime) override;
		void on_render() override;
		void on_imgui_render() override;
	};
}
