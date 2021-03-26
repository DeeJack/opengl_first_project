#include "Sorting.h"

#include <functional>

#include "sorting_utils.h"
#include "../../util.h"
#include "../../shapes/2d/Rectangle.h"
#include "glm/fwd.hpp"
#include "glm/gtx/transform.hpp"
#include "imgui/imgui.h"

namespace test
{
	/*
	 * TODO: rifare il draw in modo che non ci sia l'array di rettangoli ma un solo
	 * rettangolo a cui vengono cambiate le coordinate?
	 * TODO: in sorting utils cambiare le positions, non i rettangoli, altrimenti
	 * un elemento non viene renderizzato per un certo periodo di tempo
	 */
	const int WIDTH = 1280;
	int _comparisons = 0;
	Sorting::Sorting() :
		_shader("res/shaders/Basic.shader")
	{
		init();
	}

	Sorting::~Sorting()
	{
		for (const auto& x : _rectangles)
			delete x;
	}

	void Sorting::init()
	{
		int height;
		get_window_size(&window_width, &height);
		const int rectangle_width = window_width / rectangles_count;
		_shader.bind();
		for (int i = 0; i != rectangles_count; ++i)
		{
			const float x = rectangle_width * static_cast<float>(i);
			const int value = random_number(10, 500);
			auto pos = glm::vec2(x, 0.F);
			auto* rec = new Rectangle(pos, rectangle_width - 5, static_cast<float>(value), &_shader);
			_sortingElements.emplace_back(SortingElement{ rec, static_cast<float>(value), pos });
			_positions.emplace_back(pos);
			_rectangles.emplace_back(rec);
		}
	}

	void Sorting::on_render()
	{
		glm::mat4 model = glm::translate(glm::mat4(1.0F), translation);
		_shader.bind();
		if (_ready)
		{
			_shapes_mutex.lock();
			for (int i = 0; i != _sortingElements.size(); ++i)
				_sortingElements[i].object->set_position(_positions[i]);
			_ready = false;
			_shapes_mutex.unlock();
		}
		const glm::mat4 mvp = proj * view * model;
		_shader.bind();
		_shader.set_uniform_mat4f("u_mvp", mvp);
		for (const auto& x : _rectangles)
		{
			_renderer.draw(*x);
		}
	}

	void Sorting::on_imgui_render()
	{
		ImGui::Begin("Hello, world!");  // Create a window called "Hello, world!" and append into it.
		ImGui::SliderFloat3("Translation", &translation.x, -100.0F, 500.0F);
		if (ImGui::Button("Change color"))
		{
			for (const auto& rec : _rectangles)
			{
				auto color = random_color();
				rec->set_color(color);
			}
		}
		if (ImGui::Button("Randomize")) {
			for (const auto& x : _rectangles)
				delete x;
			_rectangles.clear();
			_sortingElements.clear();
			for (int i = 0; i != rectangles_count; ++i)
			{
				float x = 22 * static_cast<float>(i);
				int value = random_number(10, 500);
				auto pos = glm::vec2(x, 0.F);
				auto* rec = new Rectangle(pos, 20.F, static_cast<float>(value), &_shader);
				_sortingElements.emplace_back(SortingElement{ rec, static_cast<float>(value), pos });
				_positions.emplace_back(pos);
				_rectangles.push_back(rec);
			}
		}
		if (ImGui::Button("Bubble")) {
			_comparisons = 0;
			std::thread* bubble_thread = new std::thread(bubble_sort, std::ref(_sortingElements), std::ref(_shapes_mutex), std::ref(_ready), std::ref(_comparisons));
		}
		if (ImGui::Button("Insertion")) {
			_comparisons = 0;
			std::thread* insertion_thread = new std::thread(insertion_sort, std::ref(_sortingElements), std::ref(_shapes_mutex), std::ref(_ready), std::ref(_comparisons));
		}
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0F / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Text("Elements: %d", rectangles_count);
		ImGui::Text("Comparisons: %d", _comparisons);
		ImGui::End();
	}
}
