#pragma once
#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"
#include "lab_m1/tema1/duck.h"

/*
	NAME:	Dumitrescu Alexandra
	GROUP:	333CA
*/
namespace animations
{
	void GenerateEntryDirection(float &directionAngle, float &positionX, float &positionY);

	void MoveDuck(duck::Duck *duck,
				float deltaTimeSeconds,
				float logicX, float logicY,
				glm::mat3* visMatrix);
}
