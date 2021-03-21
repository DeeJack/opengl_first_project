#pragma once
#include "../Shape.h"

class Polygon : public Shape
{
private:
public:
	Polygon(const std::vector<glm::vec2> positions, Shader* shader) : Shape()
	{
		throw "Not implemented";
		const unsigned int indexes[] = { 0 , 1, 2 };
		auto va = new VertexArray();
		/*for (const glm::vec2& pos : positions)
		{
			auto vb = new VertexBuffer(positions, 3 * 2 * sizeof(float));
			BufferLayout layout;
			layout.push<float>(2);
			va->add_buffer(*vb, layout);
		}*/
		IndexBuffer* ib = new IndexBuffer(indexes, 3);
		set_index_buffer(ib);
		set_vertex_array(va);
		set_shader(shader);
	}

	Polygon() = default;
};
