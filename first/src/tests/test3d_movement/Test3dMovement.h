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
		glm::mat4 _proj = glm::ortho(0.0F, 1280.0F, 0.0F, 720.0F, -500.0F, 500.0F);
		glm::mat4 _view = glm::translate(glm::mat4(1.0F), glm::vec3(0.0F, 1.0F, 0.0F));
		glm::vec3 _translation = glm::vec3(0, 0, -200);
		Texture _texture;
		double _horizontal_angle = 3.14F;
		double _vertical_angle = 0.0F;
		float _initial_fo_v = 45.F;
		float _speed = 75.0F;
		float _mouse_speed = 0.5F;
		glm::vec3 _position = glm::vec3(0.0F, 0.0F, 0.0F);
		bool _paused = false;
	public:
		Test3dMovement();
		~Test3dMovement() override;

		void compute_mouse_position(float deltaTime);

		void on_update(float deltaTime) override;
		void on_render() override;
		void on_imgui_render() override;
	};
}
