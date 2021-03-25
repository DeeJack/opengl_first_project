#include "Test3dMovement.h"


#include "../../util.h"
#include "../../textures/Texture.h"
#include "imgui/imgui.h"

namespace test
{
	Test3dMovement::Test3dMovement()
		: _shader("res/shaders/basic3d.shader")
	{
		_shader.bind();
		glDisable(GL_BLEND);
		float colors[] = {
			 1.F, 0.F, 0.F,
			1.F, 0.3F, 0.F,
			1.F, 0.6F, 0.F,
			0.5F, 1.F, 0.F,
			0.F, 1.F, 0.F,
			0.F, 1.F, 1.F,
			0.F, 0.6F, 1.F,
			0.6F, 0.F, 1.F,
		};
		_cube = new Cube(glm::vec3(100, 100, 100), glm::vec3(300, 300, 300), &_shader);
		//float textureCoords[] = {
		//	0.0F, 0.0F,
		//	1.0F, 0.0F,
		//	1.0F, 1.0F,
		//0.0F, 1.0F
		//};
		//int texInds[6] = { 0, 1, 3, 3, 1, 2 };
		//float textureBuffer[12 * 6];
		//for (int i = 0; i < 36; i += 2) {
		//	textureBuffer[i * 2 + 0] = textureCoords[texInds[i % 4]];
		//	textureBuffer[i * 2 + 1] = textureCoords[texInds[(i + 1) % 4]];
		//}
		
		_cube->add_data(colors, 8 * 3);
		_shader.bind();
		//texture.load("res/textures/earth.png");
		//texture.bind();
		//_shader.set_uniform1i("u_texture", 0);
		glm::vec3 firstBase(400, 100, 100);
		glm::vec3 secondBase(700, 100, 400);
		glm::vec3 top(550, 400, 200);
		_pyramid = new Pyramid(firstBase, secondBase, top, &_shader);
	}

	Test3dMovement::~Test3dMovement()
	{
		delete _cube;
		delete _pyramid;
	}
	
	bool paused = false;
	void Test3dMovement::compute_mouse_position(float deltaTime)
	{
		double xpos, ypos;
		int width, height;
		get_mouse_position(&xpos, &ypos);
		get_window_size(&width, &height);
		
		// Compute new orientation
		horizontal_angle += mouse_speed * deltaTime * (static_cast<double>(width) / 2 - xpos);
		vertical_angle += mouse_speed * deltaTime * (static_cast<double>(height) / 2 - ypos);

		log("New angles: " + std::to_string(horizontal_angle) + ", " + std::to_string(vertical_angle));
		
		// Direction : Spherical coordinates to Cartesian coordinates conversion
		glm::vec3 direction(
			cos(vertical_angle) * sin(horizontal_angle),
			sin(vertical_angle),
			cos(vertical_angle) * cos(horizontal_angle)
		);

		// Right vector
		glm::vec3 right = glm::vec3(
			sin(horizontal_angle - 3.14f / 2.0f),
			0,
			cos(horizontal_angle - 3.14f / 2.0f)
		);


		// Up vector : perpendicular to both direction and right
		glm::vec3 up = glm::cross(right, direction);
		GLFWwindow* window = current_window();
		
		// Move forward
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			position += direction * deltaTime * speed;
		}
		// Move backward
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			position -= direction * deltaTime * speed;
		}
		// Strafe right
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			position += right * deltaTime * speed;
		}
		// Strafe left
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			position -= right * deltaTime * speed;
		}
		// Strafe left
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			paused = !paused;
		}
		if (paused)
			return;
		set_mouse_position(width / 2.F, height / 2.F);
		
		// Projection matrix : 45&deg; Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
		proj = glm::perspective(glm::radians(initialFoV), 16.0F / 9.0F, 0.1F, 600.0F);
		// Camera matrix
		view = glm::lookAt(
			position,           // Camera is here
			position + direction, // and looks here : at the same position, plus "direction"
			up                  // Head is up (set to 0,-1,0 to look upside-down)
		);

		//float FoV = initialFoV - 5 * glfwCursor();
	}

	void Test3dMovement::on_update(float deltaTime)
	{
		compute_mouse_position(deltaTime);
	}

	void Test3dMovement::on_render()
	{
		glm::mat4 model = glm::translate(glm::mat4(1.0F), translation);
		const glm::mat4 mvp = proj * view * model;
		_shader.set_uniform_mat4f("u_mvp", mvp);
		_renderer.draw(*_cube);
		_renderer.draw(*_pyramid);
	}

	void Test3dMovement::on_imgui_render()
	{
		ImGui::Begin("Hello, world!");  // Create a window called "Hello, world!" and append into it.
		ImGui::SliderFloat3("Translation", &translation.x, -500.0F, 500.0F);
		ImGui::End();
	}
}
