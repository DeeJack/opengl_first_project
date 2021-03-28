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
	 * TODO: in sorting utils cambiare le positions, non i rettangoli, altrimenti
	 * un elemento non viene renderizzato per un certo periodo di tempo
	 */
	int comparisons = 0;

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

	void Sorting::load_rectangles()
	{
		for (const auto& x : _rectangles)
			delete x;
		_rectangles.clear();
		_sorting_elements.clear();
		_positions.clear();
		const auto rectangle_width = _window_width / _rectangles_count;
		_shader.bind();
		for (int i = 0; i != _rectangles_count; ++i)
		{
			const auto x = static_cast<float>(rectangle_width * i);
			const auto value = random_number(10, 500);
			auto pos = glm::vec2(x, 0.F);
			auto* rec = new Rectangle(pos, static_cast<float>(rectangle_width - 5), static_cast<float>(value));
			_sorting_elements.emplace_back(SortingElement{rec, static_cast<float>(value), pos});
			_positions.emplace_back(pos);
			_rectangles.emplace_back(rec);
		}
	}

	void Sorting::init()
	{
		int height;
		get_window_size(&_window_width, &height);
		load_rectangles();
	}

	void Sorting::on_render()
	{
		const glm::mat4 model = glm::translate(glm::mat4(1.0F), _translation);
		_shader.bind();
		if (_ready)
		{
			_shapes_mutex.lock();
			for (int i = 0; i != static_cast<int>(_sorting_elements.size()); ++i)
				_sorting_elements[i].object->set_position(_positions[i]);
			_ready = false;
			_shapes_mutex.unlock();
		}
		const glm::mat4 mvp = _proj * _view * model;
		_shader.bind();
		_shader.set_uniform_mat4f("u_mvp", mvp);
		for (const auto& x : _rectangles)
		{
			_renderer.draw(*x, _shader);
		}
	}

	void Sorting::on_imgui_render()
	{
		ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and append into it.
		ImGui::SliderFloat3("Translation", &_translation.x, -100.0F, 500.0F);
		if (ImGui::Button("Change color"))
		{
			for (const auto& rec : _rectangles)
			{
				auto color = random_color();
				rec->set_color(color);
			}
		}
		if (ImGui::Button("Randomize"))
		{
			load_rectangles();
		}
		if (ImGui::Button("Bubble"))
		{
			comparisons = 0;
			std::thread bubble_thread(bubble_sort, std::ref(_sorting_elements), std::ref(_shapes_mutex),
			                          std::ref(_ready), std::ref(comparisons));
			bubble_thread.detach();
		}
		if (ImGui::Button("Insertion"))
		{
			comparisons = 0;
			std::thread insertion_thread(insertion_sort, std::ref(_sorting_elements), std::ref(_shapes_mutex),
			                             std::ref(_ready), std::ref(comparisons));
			insertion_thread.detach();
		}
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0F / ImGui::GetIO().Framerate,
		            ImGui::GetIO().Framerate);
		ImGui::Text("Elements: %d", _rectangles_count);
		ImGui::Text("Comparisons: %d", comparisons);
		ImGui::End();
	}
}
