#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"

#include "renderer/Renderer.h"
#include "buffers/VertexBuffer.h"
#include "buffers/IndexBuffer.h"
#include "buffers/VertexArray.h"
#include "imgui/imgui_impl_opengl3.h"
#include "shaders/Shader.h"
#include "textures/Texture.h"

// Create an array with the positions with no duplicate vertexes
// The first 2 floats are the position of the vertex, the last 2 are the coordinates of the texture
const float positions[] = {
	100.0F, 100.0F, 0.0F, 0.0F, // 0
	200.0F, 100.0F, 1.0F, 0.0F,// 1
	200.0F, 200.0F, 1.0F, 1.0F,// 2
	100.0F, 200.0F, 0.0F, 1.0F// 3
};

// Create an array explaining the indices of the vertex to draw
// The first triangle is 0, 1, 2, and the second is 2, 3, 0
const unsigned int indices[] = {
	0, 1, 2,
	2, 3, 0
};

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
		GLFWwindow* window = glfwCreateWindow(960, 540, "asd", nullptr, nullptr);
		if (!window)
		{
			glfwTerminate();
			return -1;
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(window);

		glfwSwapInterval(10);

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
	} catch (const std::exception& e)
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
	
	const VertexBuffer vb(positions, 4 * 4 * sizeof(float));
	BufferLayout layout;
	layout.push<float>(2);
	layout.push<float>(2);

	VertexArray va;
	va.add_buffer(vb, layout);

	const IndexBuffer ib(indices, 6);

	Shader shader("res/shaders/Basic.shader");
	shader.bind();

	const Texture texture("res/textures/earth.png");
	texture.bind();
	shader.set_uniform1i("u_texture", 0); // Slot of the texture

	// The projection specifies the space we are working in. It will transform the positions of the vertex in the -1,1 positions expected by OpenGL
	const glm::mat4 proj = glm::ortho(0.0F, 960.0F, 0.0F, 540.0F, -1.0F, 1.0F);
	// The view controls the camera. We don't actually have a camera, so we need to translate all our object to a certain direction based on the camera
	// Translate the view to the left by 100 units (the first is the x)
	const glm::mat4 view = glm::translate(glm::mat4(1.0F), glm::vec3(-100.0F, 0.0F, 0.0F));
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

	float r = 0.0F;
	float increment = 0.005F;

	glm::vec3 translation = glm::vec3(200, 200, 0);
	
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		renderer.clear();
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		
		const glm::mat4 model = glm::translate(glm::mat4(1.0F), translation);
		const glm::mat4 mvp = proj * view * model;
		shader.set_uniform_mat4f("u_mvp", mvp);

		shader.bind();
		shader.set_uniform4f("u_Color", r, 0.3F, 0.8F, 1.0F);
		// 4 because they are 4 elements, f because they are float
		renderer.draw(va, ib, shader);

		if (r > 1.0F)
			increment = -0.005F;
		else if (r < 0.0F)
			increment = 0.005F;

		r += increment;

		{
			ImGui::Begin("Hello, world!");  // Create a window called "Hello, world!" and append into it.
			ImGui::SliderFloat3("Translation", &translation.x, 0.0F, 500.0F);
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		/* Poll for and process events */
		GLCall(glfwPollEvents());

		/* Swap front and back buffers */
		GLCall(glfwSwapBuffers(window));
	}
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}