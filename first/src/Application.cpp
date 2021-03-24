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
#include "stb_image/stb_image.h"
#include "tests/TestClearColor.h"
#include "tests/TestMenu.h"
#include "tests/sorting/Sorting.h"

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
		int _width = 0, _height = 0, _bpp = 0; // Bits per pixel
		stbi_set_flip_vertically_on_load(1); // OpenGL expect the texture to start from the bottom left
		unsigned char* _local_buffer = stbi_load("res/textures/earth.png", &_width, &_height, &_bpp, 4); // 4 because R, G, B, A

		glfwSetWindowIcon(window, 1, new GLFWimage{ _width, _height, _local_buffer });

		if (_local_buffer)
			stbi_image_free(_local_buffer);

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

	//test::TestClearColor test;
	test::TestMenu test;
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		renderer.clear();

		test.on_update(0.F);
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