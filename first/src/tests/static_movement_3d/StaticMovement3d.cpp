#include "StaticMovement3d.h"
#include "../../util.h"
#include "../../shapes/2d/Rectangle.h"
#include "imgui/imgui.h"

namespace test
{
	StaticMovement3d::StaticMovement3d()
	{
		_shader.bind();
		glDisable(GL_BLEND);
		int width, height;
		get_window_size(&width, &height);
		_proj = glm::ortho(0.F, static_cast<float>(width), 0.F, static_cast<float>(height), -500.F, 500.F);
		_cube.fillWithIndexes();
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
		_cube.add_data(colors, 8 * 3);
		//glm::vec3 firstBase(400, 100, 100);
		//glm::vec3 secondBase(700, 100, 400);
		//glm::vec3 top(550, 400, 200);
		//_pyramid = new Pyramid(firstBase, secondBase, top);
		//_pyramid->add_data(colors, 5 * 3);
	}

	StaticMovement3d::~StaticMovement3d()
	{
	}

	glm::mat4 rotate_around_point(float rotationAngle, glm::vec3 rotationPoint, glm::vec3 rotationAxis)
	{
		/*
		 * Translation around a point
		 * 1) Translate the matrix to the point we want to rotate
		 * 2) Create an inverse translation to reverse the translation
		 * 3) Create the rotation matrix
		 * 4) Apply the translation, apply the rotation, reverse the translation and lastly apply everything to the model
		 */
		const auto translation = glm::translate(glm::mat4(1.F), rotationPoint);
		const auto invTranslate = glm::inverse(translation);
		const auto rotationMatrix = glm::rotate(rotationAngle, rotationAxis);
		return translation * rotationMatrix * invTranslate;
	}

	void StaticMovement3d::compute_mouse_movement(float deltaTime)
	{
		const double MOUSE_SPEED = 50.F;
		double xpos, ypos;
		int width, height;
		get_mouse_position(&xpos, &ypos);
		get_window_size(&width, &height);


		// Compute new orientation
		const float horizontal_angle = MOUSE_SPEED * deltaTime * (static_cast<double>(width) / 2 - xpos);
		const auto vertical_angle = MOUSE_SPEED * deltaTime * (static_cast<double>(height) / 2 - ypos);

		log("New angles: " + std::to_string(horizontal_angle) + ", " + std::to_string(vertical_angle));

		glm::vec3 rotationAxis;

		if (horizontal_angle >= 0)
			rotationAxis = glm::vec3(0.F, 1.F, 0.F);
		else
			rotationAxis = glm::vec3(0.F, -1.F, 0.F);
		
		const auto rotation = glm::rotate(glm::radians(horizontal_angle), rotationAxis);
		_view = rotation * _view;

		set_mouse_position(static_cast<double>(width) / 2.F, static_cast<double>(height) / 2.F);
	}
	
	void StaticMovement3d::on_update(float deltaTime)
	{
		if (_translation != _last_translation)
		{
			_model = glm::translate(glm::mat4(1.F), _translation);
			_last_translation = _translation;
		}
		compute_mouse_movement(deltaTime);
		//const auto rotation = rotate_around_point(glm::radians(80.F * deltaTime), glm::vec3(1280 / 2, 100, 0));
		const auto rotation = rotate_around_point(glm::radians(80.F * deltaTime), 
			glm::vec3(500, 300, 100), glm::vec3(1.F, 1.F, 0.F));
		//_model = rotation * _model ;
	}

	void StaticMovement3d::on_render()
	{
		const auto mvp = _proj * _view * _model;
		_shader.bind();
		_shader.set_uniform_mat4f("u_mvp", mvp);
		//_renderer.draw(*_pyramid, _shader);
		_renderer.draw(_cube, _shader);
	}

	void StaticMovement3d::on_imgui_render()
	{
		ImGui::SliderFloat3("Translation", &_translation.x, -500.0F, 500.0F);
	}
}
