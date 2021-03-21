#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <thread>
#include <chrono>
#include <mutex>


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "renderer/Renderer.h"
#include "buffers/VertexArray.h"
#include "shaders/Shader.h"
#include "shapes/rectangle/Rectangle.h"
#include "util.h"
#include "sorting/SortingElement.h"
#include "tests/TestClearColor.h"

void run(GLFWwindow* window);
std::mutex shapes_mutex;
bool ready = false;

int main() noexcept
{
	try
	{
		/* Initialize the library */
		if (!glfwInit())
			return -1;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		/* Create a windowed mode window and its OpenGL context */
		GLFWwindow* window = glfwCreateWindow(1280, 720, "asd", nullptr, nullptr);
		if (!window)
		{
			glfwTerminate();
			return -1;
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(window);

		//glfwSwapInterval(10);

		if (glewInit() != GLEW_OK)
		{
			std::cout << "An error occurred initializing GLEW*\n";
			return 1;
		}

		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(reinterpret_cast<GLDEBUGPROC>(LOG_ERROR), nullptr);

		std::cout << glGetString(GL_VERSION) << std::endl;

		run(window);

		glfwTerminate();
	}
	catch (const std::exception& e)
	{
		std::cout << "Something went wrong\n" << e.what() << std::endl;
	}
	return 0;
}

void on_finish(std::vector<SortingElement>& elements)
{
	for (int i = 0; i != elements.size(); ++i)
	{
		elements[i].object->set_color(normalize_color(255, 0, 0));
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	for (int i = 0; i != elements.size(); ++i)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		elements[i].object->set_color(normalize_color(255, 255, 255));
	}
}

void bubble_sort(std::vector<SortingElement>& elements)
{
	for (int i = 0; i != elements.size(); ++i)
	{
		elements[i].object->set_color(normalize_color(255, 0, 0));
		for (int j = 0; j != elements.size(); ++j)
		{
			elements[j].object->set_color(normalize_color(102, 255, 51));
			if (elements[i].value < elements[j].value)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				shapes_mutex.lock();
				ready = true;
				//auto temp = elements[i].position;
				//elements[i].position = elements[j].position;
				//elements[j].position = temp;
				
				elements[j].object->set_color(normalize_color(255, 255, 255));
				elements[i].object->set_color(normalize_color(255, 255, 255));

				auto temp2 = elements[i];
				elements[i] = elements[j];
				elements[j] = temp2;
				shapes_mutex.unlock();
			}
			elements[j].object->set_color(normalize_color(255, 255, 255));
		}
		elements[i].object->set_color(normalize_color(255, 255, 255));
	}
	on_finish(elements);
}

void insertion_sort(std::vector<SortingElement>& elements)
{
	for (int i = 1; i != elements.size(); ++i)
	{
		SortingElement key = elements[i];
		elements[i].object->set_color(normalize_color(255, 0, 0));
		std::cout << "Selecting element " << i << ": " << key.value << std::endl;
		int j = i - 1;
		while (j >= 0 && elements[j].value > key.value)
		{
			std::cout << "\tSwitching with element " << j << ": " << elements[j].value << std::endl;
			elements[j + 1].object->set_color(normalize_color(0, 255, 0));
			elements[j].object->set_color(normalize_color(102, 255, 51));

			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			
			shapes_mutex.lock();

			ready = true;
			elements[j + 1].object->set_color(normalize_color(255, 255, 255));
			elements[j].object->set_color(normalize_color(255, 255, 255));
			
			elements[j + 1] = elements[j];
			shapes_mutex.unlock();
			
			--j;
		}
		elements[i].object->set_color(normalize_color(255, 255, 255));
		
		shapes_mutex.lock();

		ready = true;
		elements[j + 1] = key;
		shapes_mutex.unlock();
		std::cout << "\nCurrent situation: ";

		for (const auto& x : elements)
		{
			std::cout << x.value << ", ";
		}
		std::cout << "\n";
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	on_finish(elements);
}

// TODO: I don't like that everything needs to be in a single array
void run(GLFWwindow* window) {
	// Source -> what we are rendering, destination: what is already rendered
	// SRC_ALPHA: the alpha (rgba) of the source, for example for something transparent it's 0
	// ONE_MINUS_SRC_ALPHA: 1 - SRC_ALPHA, 1 minus the alpha of the source
	// If the source it's transparent, it takes the background
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	std::vector<Shape*> rectangles;
	std::vector<SortingElement> sortingElements;
	std::vector<glm::vec2> positions;
	//std::vector<float> values;

	Shader shader("res/shaders/Basic.shader");
	shader.bind();

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

	const Renderer renderer;

	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	const char* glsl_version = "#version 130";
	ImGui_ImplOpenGL3_Init(glsl_version);

	test::TestClearColor test;
	
	glm::vec3 translation = glm::vec3(0, 0, 0);
	glm::vec3 cameraTranslation = glm::vec3(0.0F, -1.0F, 0.0F);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		renderer.clear();

		test.on_update(0.F);
		//test.on_render();
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

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
			renderer.draw(*x);
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
				std::thread* bubble_thread = new std::thread(bubble_sort, std::ref(sortingElements));
				//bubble_thread->join();
			}
			if (ImGui::Button("Insertion")) {
				std::thread* insertion_thread = new std::thread(insertion_sort, std::ref(sortingElements));
				//insertion_thread->join();
			}
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0F / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}
		test.on_imgui_render();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		/* Poll for and process events */
		GLCall(glfwPollEvents());
		/* Swap front and back buffers */
		GLCall(glfwSwapBuffers(window));
	}

	for (const auto& x : rectangles)
		delete x;

	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}