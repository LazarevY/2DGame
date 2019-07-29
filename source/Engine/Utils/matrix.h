#pragma once
#include "types.h"
#include <glm/gtx/matrix_transform_2d.hpp>

namespace  matrix
{
	matrix3 vertexNormalizeMatrix3x3(float width, float height);
	matrix3 textureNormalizeMatrix3x3(float width, float height);
}