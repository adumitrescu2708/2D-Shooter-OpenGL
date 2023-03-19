#pragma once
#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"

/*
    NAME:	Dumitrescu Alexandra
    GROUP:	333CA
*/
namespace object2D
{
    /* Functions for generating basic 2D poly */
    Mesh* CreateSquare(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateTriangle(const std::string& name, glm::vec3 baseCenter, float length, glm::vec3 color);
    Mesh* CreateCircle(const std::string& name, glm::vec3 center, float radius, glm::vec3 color);
    Mesh* CreateRectangle(const std::string& name, glm::vec3 leftBottomCorner, float length, float weight, glm::vec3 color, bool fill = false);
    Mesh* CreateRomb(const std::string& name, glm::vec3 center, float length, float weight, glm::vec3 color);
}
