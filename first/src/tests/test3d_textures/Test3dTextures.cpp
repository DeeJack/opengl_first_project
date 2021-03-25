#include "Test3dTextures.h"


#include "../../textures/Texture.h"
#include "imgui/imgui.h"

namespace test
{
	Test3dTextures::Test3dTextures()
		: _shader("res/shaders/basic3d_texture.shader")
	{
		_shader.bind();
		glDisable(GL_BLEND);
		/*float colors[] = {
			 1.F, 0.F, 0.F,
			1.F, 0.3F, 0.F,
			1.F, 0.6F, 0.F,
			0.5F, 1.F, 0.F,
			0.F, 1.F, 0.F,
			0.F, 1.F, 1.F,
			0.F, 0.6F, 1.F,
			0.6F, 0.F, 1.F,
		};*/
		_cube = new CubeTest(glm::vec3(100, 100, 100), glm::vec3(300, 300, 300), &_shader);
		float textureCoords[] = {
			0.0F, 0.0F,
			1.0F, 0.0F,
			1.0F, 1.0F,
			0.0F, 1.0F
		};
		int texInds[6] = { 0, 1, 3, 1, 2, 3 };
		float textureBuffer[2 * 6 * 6];
		int index = 0;
		for (int i = 0; i < 36 * 2; i += 2) {
			textureBuffer[i] = textureCoords[texInds[index % 6] * 2];
			textureBuffer[i + 1] = textureCoords[texInds[index % 6] * 2 + 1];
			index++;
		}

		std::cout << "Texture buffer: \n";
		for (int i = 1; i <= 36 * 2; i++) {
			std::cout << textureBuffer[i - 1] << ", ";
			if (i % 2 == 0)
				std::cout << "\n";
		}
		
		_cube->add_data(textureBuffer, 2 * 6 * 6);
		_shader.bind();
		texture.load("res/textures/earth.png");
		texture.bind();
		_shader.set_uniform1i("u_texture", 0);
		glm::vec3 firstBase(400, 100, 100);
		glm::vec3 secondBase(700, 100, 400);
		glm::vec3 top(550, 400, 200);
		//_pyramid = new Pyramid(firstBase, secondBase, top, &_shader);
	}

	Test3dTextures::~Test3dTextures()
	{
		delete _cube;
		//delete _pyramid;
	}

	void Test3dTextures::on_update(float deltaTime)
	{
	}

	void Test3dTextures::on_render()
	{
		glm::mat4 model = glm::translate(glm::mat4(1.0F), translation);
		if (_camera_rotations[0] != _last_rotations[0]) {
			view = glm::rotate(glm::mat4(1.0F),  glm::radians(_camera_rotations[0]), glm::vec3(1, 0, 0));
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
		const glm::mat4 mvp = proj * view * model;
		_shader.set_uniform_mat4f("u_mvp", mvp);
		//_renderer.draw(*_cube);
		_renderer.drawWithoutIndexes(*_cube);
	}

	void Test3dTextures::on_imgui_render()
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
