#pragma once
#include "../Test.h"
#include "../../renderer/Renderer.h"
#include "../../shapes/3d/Cube.h"
#include "../../shapes/3d/Pyramid.h"
#include "../../textures/Texture.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/gtx/transform.hpp"

namespace test
{
	class Test3dMovement : public Test
	{
	private:
		Cube* _cube;
		Pyramid* _pyramid;
		Shader _shader;
		Renderer _renderer;
		glm::mat4 proj = glm::ortho(0.0F, 1280.0F, 0.0F, 720.0F, -500.0F, 500.0F);
		glm::mat4 view = glm::translate(glm::mat4(1.0F), glm::vec3(0.0F, 1.0F, 0.0F));
		glm::vec3 translation = glm::vec3(0, 0, -200);
		Texture texture;
		double horizontal_angle = 3.14F;
		double vertical_angle = 0.0F;
		float initialFoV = 45.F;
		float speed = 75.0F;
		float mouse_speed = 0.5F;
		glm::vec3 position = glm::vec3(0.0F, 0.0F, 0.0F);
	public:
		Test3dMovement();
		virtual ~Test3dMovement() override;

		void compute_mouse_position(float deltaTime);
		
		void on_update(float deltaTime) override;
		void on_render() override;
		void on_imgui_render() override;
	};
}
