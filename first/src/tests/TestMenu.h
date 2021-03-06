#pragma once
#include "Test.h"
#include "TestClearColor.h"
#include "imgui/imgui.h"
#include "pong/Pong.h"
#include "seven_segment/SevenSegmentTest.h"
#include "sorting/Sorting.h"
#include "test3d/Test3d.h"
#include "test3d_movement/Test3dMovement.h"
#include "static_movement_3d/StaticMovement3d.h"
#include "test3d_textures/Test3dTextures.h"
#include "textures/TestTextures.h"

namespace test
{
	class TestMenu : Test {
	private:
		Test* _current_test = new TestTextures();
	public:

		virtual ~TestMenu() override
		{
			delete _current_test;
		}
		
		void on_update(float deltaTime) override
		{
			_current_test->on_update(deltaTime);
		}

		void on_render() override
		{
			_current_test->on_render();
		}

		void on_imgui_render() override
		{
			ImGui::Text("Select the test to show:");
			if (ImGui::Button("TestClearColor"))
			{
				delete _current_test;
				_current_test = new TestClearColor();
			}
			else if (ImGui::Button("TestSort"))
			{
				delete _current_test;
				_current_test = new Sorting();
			}
			else if (ImGui::Button("Textures"))
			{
				delete _current_test;
				_current_test = new TestTextures();
			}
			else if (ImGui::Button("3d"))
			{
				delete _current_test;
				_current_test = new Test3d();
			}
			else if (ImGui::Button("3d movement"))
			{
				delete _current_test;
				_current_test = new Test3dMovement();
			}
			else if (ImGui::Button("3d textures"))
			{
				delete _current_test;
				_current_test = new Test3dTextures();
			}
			else if (ImGui::Button("3d movement 2"))
			{
				delete _current_test;
				_current_test = new StaticMovement3d();
			}
			else if (ImGui::Button("Seven segment"))
			{
				delete _current_test;
				_current_test = new SevenSegmentTest();
			}
			else if (ImGui::Button("Pong"))
			{
				delete _current_test;
				_current_test = new Pong();
			}

			_current_test->on_imgui_render();
		}
	};
}
