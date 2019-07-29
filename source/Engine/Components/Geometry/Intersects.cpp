#include "Intersects.h"

namespace intersection
{
	bool intersection(const AARectangle&  rectangle_1, const AARectangle& rectangle_2)
	{
		const vector2 rec1_min = rectangle_1.getMin();
		const vector2 rec1_max = rectangle_1.getMax();

		const vector2 rec2_min = rectangle_2.getMin();
		const vector2 rec2_max = rectangle_2.getMax();

		return (rec2_min.x <= rec1_max.x) && (rec1_min.x <= rec2_max.x) &&
			(rec2_min.y <= rec1_max.y) && (rec1_min.y <= rec2_max.y);
	}
	vector2 getOverlaps(const AARectangle & rectangle_1, const AARectangle & rectangle_2)
	{
		Interval2D r1_x = rectangle_1.getIntervalX();
		Interval2D r1_y = rectangle_1.getIntervalY();

		Interval2D r2_x = rectangle_2.getIntervalX();
		Interval2D r2_y = rectangle_2.getIntervalY();

		float overlapX = 0;
		if(!(r1_x.min.x > r2_x.min.x && r1_x.max.x < r2_x.max.x || r2_x.min.x > r1_x.min.x && r2_x.max.x < r1_x.max.x))
		{
			overlapX = fminf(r1_x.max.x - r2_x.min.x, r2_x.max.x - r1_x.min.x);
		}		
		float overlapY = 0;
		if(!(r1_x.min.y > r2_x.min.y && r1_x.max.y < r2_x.max.y || r2_x.min.y > r1_x.min.y && r2_x.max.y < r1_x.max.y))
		{
			overlapY = fminf(r1_x.max.y - r2_x.min.y, r2_x.max.y - r1_x.min.y);
		}

		return vector2(overlapX, overlapY);
	}
}