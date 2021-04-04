#include "TestTextures.h"

#include <functional>


#include "../../shapes/2d/Circle.h"
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
	delete _box;
	delete _circle;
	glClearColor(0.F, 0.F, 0.F, 1.F);
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
	_circle = new Circle(glm::vec2(600.F, 400.F), 70.F);
	//_texture.load("res/textures/ball.png");
	_texture.load("res/textures/ball.png");
	_texture.bind();
	_shader.set_uniform1i("u_texture", 0);

	const float size = 100.F;
	const glm::vec2 pos(100, 100.F);
	_circle->add_texture();
	//_box = new Rectangle(pos, size, size);
	//_box->add_data(textCoord, 2 * 4);
}

void test::TestTextures::on_update(float deltaTime)
{
}

void test::TestTextures::on_render()
{
	glClearColor(1.F, 1.F, 1.F, 1.F);
	_shader.bind();
	glm::mat4 model = glm::translate(glm::mat4(1.0F), _translation);
	const glm::mat4 mvp = _proj * model;
	_shader.set_uniform_mat4f("u_mvp", mvp);
	_shader.set_uniform1b("u_is_texture", true);
	//_renderer.draw(*_box, _shader);
	_renderer.draw(*_circle, _shader);
}

void test::TestTextures::on_imgui_render()
{
	ImGui::Text("TEST");
	ImGui::SliderFloat3("Translation", &_translation.x, -100.0F, 500.0F);
}
