#include "Test3d.h"

#include "imgui/imgui.h"

namespace test
{
	Test3d::Test3d()
		: _shader("res/shaders/basic3d.shader")
	{
		_shader.bind();
		glDisable(GL_BLEND);
		_cube = new Cube(glm::vec3(100, 100, 100), glm::vec3(300, 300, 300), &_shader);
		glm::vec3 firstBase(400, 100, 100);
		glm::vec3 secondBase(700, 100, 400);
		glm::vec3 top(550, 400, 200);
		_pyramid = new Pyramid(firstBase, secondBase, top, &_shader);
	}

	Test3d::~Test3d()
	{
		delete _cube;
		delete _pyramid;
	}

	void Test3d::on_update(float deltaTime)
	{
	}

	void Test3d::on_render()
	{
		if (_camera_rotations[0] != _last_rotations[0]) {
			view = glm::rotate(glm::mat4(1.F), glm::radians(_camera_rotations[0]), glm::vec3(1, 0, 0));
			_last_rotations[0] = _camera_rotations[0];
		}
		if (_camera_rotations[1] != _last_rotations[1]) {
			view = glm::rotate(glm::mat4(1.F), glm::radians(_camera_rotations[1]), glm::vec3(0, 1, 0));
			_last_rotations[1] = _camera_rotations[1];
		}
		if (_camera_rotations[2] != _last_rotations[2]) {
			view = glm::rotate(glm::mat4(1.F), glm::radians(_camera_rotations[2]), glm::vec3(0, 0, 1));
			_last_rotations[2] = _camera_rotations[2];
		}
		if (_camera_rotations[3] != _last_rotations[3]) {
			view = glm::rotate(glm::mat4(1.F), glm::radians(_camera_rotations[3]), glm::vec3(1, 1, 0));
			_last_rotations[3] = _camera_rotations[3];
		}
		glm::mat4 model = glm::translate(glm::mat4(1.0F), translation);
		const glm::mat4 mvp = proj * view * model;
		_shader.set_uniform_mat4f("u_mvp", mvp);
		_renderer.draw(*_cube);
		_renderer.draw(*_pyramid);
	}

	void Test3d::on_imgui_render()
	{
		ImGui::Begin("Hello, world!");  // Create a window called "Hello, world!" and append into it.
		ImGui::SliderFloat3("Translation", &translation.x, -500.0F, 500.0F);
		ImGui::SliderFloat("Rotation X", &_camera_rotations[0], 0.0F, 360.0F);
		ImGui::SliderFloat("Rotation Y", &_camera_rotations[1], 0.0F, 360.0F);
		ImGui::SliderFloat("Rotation Z", &_camera_rotations[2], 0.0F, 360.0F);
		ImGui::SliderFloat("Rotation XY", &_camera_rotations[3], 0.0F, 360.0F);
		ImGui::End();
	}
}
