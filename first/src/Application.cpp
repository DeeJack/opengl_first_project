#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <thread>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "renderer/Renderer.h"
#include "buffers/VertexArray.h"
#include "util.h"
#include "tests/TestMenu.h"
#include "textures/Image.h"

void run(GLFWwindow* window);

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
		auto* image = new Image();
		image->load_image_async("res/textures/earth.png", [&window, &image]()
		{
			glfwSetWindowIcon(window, 1, new GLFWimage{ image->width(), image->height(), image->local_buffer() });
			delete image;
		});

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

void run(GLFWwindow* window) {
	// Source -> what we are rendering, destination: what is already rendered
	// SRC_ALPHA: the alpha (rgba) of the source, for example for something transparent it's 0
	// ONE_MINUS_SRC_ALPHA: 1 - SRC_ALPHA, 1 minus the alpha of the source
	// If the source it's transparent, it takes the background
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	const Renderer renderer;

	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	const char* glsl_version = "#version 330";
	ImGui_ImplOpenGL3_Init(glsl_version);

	test::TestMenu test;
	/* Loop until the user closes the window */
	double lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(window))
	{
		renderer.clear();

		const double currentTime = glfwGetTime();
		const auto deltaTime = static_cast<float>(currentTime - lastTime);
		lastTime = currentTime;
		
		test.on_update(deltaTime);
		test.on_render();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		test.on_imgui_render();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		GLCall(glfwPollEvents());
		GLCall(glfwSwapBuffers(window));
	}

	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}