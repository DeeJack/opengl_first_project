#pragma once
#include "glm/vec3.hpp"

class Scene
{
public:
	Scene(const glm::vec3& position);
	
	virtual void draw() = 0;
};
