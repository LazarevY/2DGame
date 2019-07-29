#pragma once

#include <Engine/Components/Geometry/Primitives/Rectangle.h>
#include "Primitives/Interval.h"

namespace intersection
{
	bool intersection(const AARectangle& rectangle_1, const AARectangle& rectangle_2);
	vector2 getOverlaps(const AARectangle& rectangle_1, const AARectangle& rectangle_2);
}