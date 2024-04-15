#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"



namespace figure
{
    Mesh* CreateSquare(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateDiamond(const std::string& name, glm::vec3 middle, float length, glm::vec3 color);
    Mesh* CreateHexagons(const std::string& name, glm::vec3 middle, float length, glm::vec3 color, glm::vec3 color2);
    Mesh* CreateStar(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color);
}