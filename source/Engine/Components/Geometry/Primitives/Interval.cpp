#include "Interval.h"

Interval2D::Interval2D() : min(0,0), max(1,0)
{
}

Interval2D::Interval2D(const vector2 & min, const vector2 & max) : min(min), max(max)
{

}
