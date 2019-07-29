#include "matrix.h"

namespace  matrix
{
	matrix3 vertexNormalizeMatrix3x3(float width, float height)
	{
		matrix3 result = matrix3();
		result = glm::scale(result, vector2(2.f / width, 2.f / height));
		result = glm::translate(result, vector2(width / -2.f, height / -2.f));
		return result;
	}
	matrix3 textureNormalizeMatrix3x3(float width, float height)
	{
		matrix3 result = matrix3();
		result = glm::scale(result, vector2(1.f/width, 1.f/height));
		return result;
	}
}

