#pragma once
#include <GLFW/glfw3.h>

#include <functional>
#include <random>

#include "glm/vec4.hpp"

static glm::vec4 normalize_color(short int red, short int green, short int blue, short int alpha)
{
	return glm::vec4(static_cast<float>(red) / 255.F, static_cast<float>(green) / 255.F,
		static_cast<float>(blue) / 255.F, static_cast<float>(alpha) / 255.F);
}

static glm::vec4 normalize_color(short int red, short int green, short int blue)
{
	return normalize_color(red, green, blue, static_cast<short int>(255));
}
static std::default_random_engine generator;

static glm::vec4 random_color()
{
	static std::uniform_int_distribution<short int> distribution(1, 255);
	static auto rnd = std::bind(distribution, generator);
	return normalize_color(rnd(), rnd(), rnd());
}

static int random_number(int min, int max)
{
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}

static GLFWwindow* current_window()
{
	auto* window = glfwGetCurrentContext();
	return window;
}

static void get_window_size(int* width, int* height)
{
	auto* window = current_window();
	glfwGetWindowSize(window, width, height);
}

static void get_mouse_position(double* xpos, double* ypos)
{
	auto* window = glfwGetCurrentContext();
	glfwGetCursorPos(window, xpos, ypos);
}

static void set_mouse_position(double xpos, double ypos)
{
	auto* window = glfwGetCurrentContext();
	glfwSetCursorPos(window, xpos, ypos);
}