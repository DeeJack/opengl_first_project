#include "TestTextures.h"

#include <functional>

#include "../../shapes/2d/Rectangle.h"
#include "../../textures/Texture.h"
#include "imgui/imgui.h"

test::TestTextures::TestTextures()
	: _shader("res/shaders/textures.shader")
{
	init();
}

test::TestTextures::~TestTextures()
{
	log("Deleting TestTextures");
	delete _box;
	log("Deleted TestTextures");
}

void test::TestTextures::init()
{
	const float textCoord[] = {
		0.0F, 0.0F,
		1.F, 0.0F,
		1.F, 1.F,
		0.0F, 1.F
	};
	_shader.bind();
	glEnable(GL_BLEND);
	//_textureTask = new std::thread([this] {
	_texture.load("res/textures/earth.png");
	_texture.bind();
	//});

	const float size = 600.F;
	const glm::vec2 pos(100, 100.F);
	_box = new Rectangle(pos, size, size, &_shader);
	_box->add_data(textCoord, 2 * 4);
}

void test::TestTextures::on_update(float deltaTime)
{
}

void test::TestTextures::on_render()
{
	//_texture->bind();
	glm::mat4 model = glm::translate(glm::mat4(1.0F), translation);
	const glm::mat4 mvp = proj * view * model;
	_shader.set_uniform1i("u_texture", 0);
	_shader.set_uniform_mat4f("u_mvp", mvp);
	_renderer.draw(*_box);
}

void test::TestTextures::on_imgui_render()
{
	ImGui::Text("TEST");
	ImGui::SliderFloat3("Translation", &translation.x, -100.0F, 500.0F);
}
