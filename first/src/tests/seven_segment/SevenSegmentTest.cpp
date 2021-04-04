#include "SevenSegmentTest.h"

#include <GLFW/glfw3.h>


#include "../../shapes/2d/Rectangle.h"

namespace test
{
	SevenSegmentTest::SevenSegmentTest()
	{
		_shader.bind();
		_shader.set_uniform1b("u_is_texture", false);
		_shader.set_uniform4f("u_color", 1.F, 0.F, 0.F, 1.F);
		glfwSwapInterval(60);
	}

	SevenSegmentTest::~SevenSegmentTest()
	{
		glfwSwapInterval(0);
	}

	void SevenSegmentTest::on_update(float deltaTime)
	{
		const auto first = _count % 10;
		const auto second = _count / 10;
		_seven_segments[1].show(first);
		_seven_segments[0].show(second);
		_count++;
	}

	void SevenSegmentTest::on_render()
	{
		_shader.set_uniform_mat4f("u_mvp", _projection);
		_shader.set_uniform1b("u_is_texture", false);
		for (const auto& segment : _seven_segments)
		{
			for (const auto& x : segment.get_segments())
			{
				if (x.isVisible)
					_renderer.draw(*x.seg, _shader);
				else
					_renderer.draw_no_color(*x.seg, _shader);
			}
		}
	}

	void SevenSegmentTest::on_imgui_render()
	{
	}
}
