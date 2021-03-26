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
	class Test3dTextures : public Test
	{
	private:
		Cube* _cube;
		Pyramid* _pyramid;
		Shader _shader;
		Renderer _renderer;
		const glm::mat4 proj = glm::ortho(0.0F, 1280.0F, 0.0F, 720.0F, -500.0F, 500.0F);
		glm::mat4 view = glm::translate(glm::mat4(1.0F), glm::vec3(0.0F, 1.0F, 0.0F));
		glm::vec3 translation = glm::vec3(0, 0, -200);
		float _camera_rotations[4] = {0.F, 0.F, 0.F, 0.F};
		float _last_rotations[4] = { 0.F, 0.F, 0.F, 0.F };
		Texture texture;
	public:
		Test3dTextures();
		virtual ~Test3dTextures();
		
		void on_update(float deltaTime) override;
		void on_render() override;
		void on_imgui_render() override;
	};
}
