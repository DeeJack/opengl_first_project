#include "Sorting.h"

#include <functional>
#include <mutex>



#include "../../util.h"
#include "../../shapes/rectangle/Rectangle.h"
#include "../../sorting/SortingElement.h"
#include "glm/fwd.hpp"
#include "glm/gtx/transform.hpp"
#include "imgui/imgui.h"

namespace test
{
	std::mutex shapes_mutex;
	bool ready = false;
	
	Sorting::Sorting()
	{
	}

	Sorting::~Sorting()
	{
	}

	void Sorting::on_update(float deltaTime)
	{
	}

	void Sorting::on_render()
	{
	}

	void Sorting::on_imgui_render()
	{
	}

	void trash()
	{
		Shader shader("res/shaders/Basic.shader");
		shader.bind();
		std::vector<Shape*> rectangles;
		std::vector<SortingElement> sortingElements;
		std::vector<glm::vec2> positions;
		//std::vector<float> values;
		glm::vec3 translation = glm::vec3(0, 0, 0);
		glm::vec3 cameraTranslation = glm::vec3(0.0F, -1.0F, 0.0F);

		//std::vector<glm::vec3> rectangleTranslations;
		for (int i = 0; i != 20; ++i)
		{
			float x = 30 * static_cast<float>(i);
			int value = random_number(10, 500);
			auto pos = glm::vec2(10.F + x, 0.F);
			auto* rec = new Rectangle(pos, 20.F, static_cast<float>(value), &shader);
			sortingElements.emplace_back(SortingElement{ rec, static_cast<float>(value), pos });
			positions.emplace_back(pos);
			rectangles.push_back(rec);
		}

		/*const Texture texture("res/textures/earth.png");
		texture.bind();
		shader.set_uniform1i("u_texture", 0); // Slot of the texture*/

		// The projection specifies the space we are working in. It will transform the positions of the vertex in the -1,1 positions expected by OpenGL
		const glm::mat4 proj = glm::ortho(0.0F, 1280.0F, 0.0F, 720.0F, -100.0F, 100.0F);
		// The view controls the camera. We don't actually have a camera, so we need to translate all our object to a certain direction based on the camera
		// Translate the view to the left by 100 units (the first is the x)
		glm::mat4 view = glm::translate(glm::mat4(1.0F), glm::vec3(0.0F, 0.0F, 0.0F));
		// The transformation of the object in the world
		//const glm::mat4 model = glm::translate(glm::mat4(1.0F), glm::vec3(200, 200, 0));
		// Model View Projection matrix
		//const glm::mat4 mvp = proj * view * model;

		glm::mat4 model = glm::translate(glm::mat4(1.0F), translation);
		// model = glm::rotate(model, glm::radians(45.F), cameraTranslation);
		const glm::mat4 mvp = proj * view * model;
		//shader.set_uniform_mat4f("u_mvp", mvp);

		//shader.set_uniform4f("u_color", r, 0.3F, 0.8F, 1.0F);
		if (ready)
		{
			shapes_mutex.lock();
			for (int i = 0; i != sortingElements.size(); ++i)
				sortingElements[i].object->set_position(positions[i]);
			//swappedData.first.object->set_position(swappedData.first.position);
			//swappedData.second.object->set_position(swappedData.second.position);
			ready = false;
			//rectangles[swappedData2.first]->set_position(swappedData.second);
			//rectangles[swappedData.second] = rectangles[swappedData.first];
			shapes_mutex.unlock();
		}
		for (const auto& x : rectangles)
		{
			//for (const auto& translation : rectangleTranslations)
			//{
			shader.bind();
			shader.set_uniform_mat4f("u_mvp", mvp);
			//shapes_mutex.lock();
			//renderer.draw(*x);
			//}
			//shapes_mutex.unlock();
		}

		{
			ImGui::Begin("Hello, world!");  // Create a window called "Hello, world!" and append into it.
			ImGui::SliderFloat3("Translation", &translation.x, -100.0F, 500.0F);
			ImGui::SliderFloat3("Translation camera", &cameraTranslation.x, -100.0F, 100.0F);
			if (ImGui::Button("Change color"))
			{
				for (const auto& rec : rectangles)
				{
					auto color = random_color();
					rec->set_color(color);
				}
			}
			if (ImGui::Button("Randomize")) {
				for (const auto& x : rectangles)
					delete x;
				rectangles.clear();
				sortingElements.clear();
				for (int i = 0; i != 20; ++i)
				{
					float x = 30 * static_cast<float>(i);
					int value = random_number(10, 500);
					auto pos = glm::vec2(10.F + x, 0.F);
					auto* rec = new Rectangle(pos, 20.F, static_cast<float>(value), &shader);
					sortingElements.emplace_back(SortingElement{ rec, static_cast<float>(value), pos });
					positions.emplace_back(pos);
					rectangles.push_back(rec);
				}
			}
			if (ImGui::Button("Bubble")) {
				//std::thread* bubble_thread = new std::thread(bubble_sort, std::ref(sortingElements));
				//bubble_thread->join();
			}
			if (ImGui::Button("Insertion")) {
				//std::thread* insertion_thread = new std::thread(insertion_sort, std::ref(sortingElements));
				//insertion_thread->join();
			}
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0F / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}
		for (const auto& x : rectangles)
			delete x;
	}
}
