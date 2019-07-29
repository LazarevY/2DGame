#pragma once
#include <Engine/Utils/types.h>
struct  Interval2D
{
	vector2 min;
	vector2 max;

	Interval2D();
	Interval2D(const vector2& min, const vector2& max);
};