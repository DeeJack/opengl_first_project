#pragma once
#include <mutex>

#include "../Test.h"
#include "../../renderer/Renderer.h"
#include "../../shaders/Shader.h"
#include "SortingElement.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/gtx/transform.hpp"

namespace test
{
	class Sorting : public Test
	{
	private:
		std::mutex _shapes_mutex;
		bool _ready = false;
		Shader _shader;
		std::vector<Shape*> _rectangles;
		std::vector<SortingElement> _sorting_elements;
		std::vector<glm::vec2> _positions;
		const glm::mat4 _proj = glm::ortho(0.0F, 1280.0F, 0.0F, 720.0F, -100.0F, 100.0F);
		glm::mat4 _view = glm::translate(glm::mat4(1.0F), glm::vec3(0.0F, 0.0F, 0.0F));
		glm::vec3 _translation = glm::vec3(0, 0, 0);
		Renderer _renderer;
		const int _rectangles_count = 55;
		int _window_width;

		void load_rectangles();
	public:
		Sorting();
		~Sorting() override;

		void init();

		void on_render() override;
		void on_imgui_render() override;
	};
}
