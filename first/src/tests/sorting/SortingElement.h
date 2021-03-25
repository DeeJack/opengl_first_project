#pragma once
#include "../shapes/Shape.h"

struct SortingElement
{
	Shape* object;
	float value;
	glm::vec2 position;
};
