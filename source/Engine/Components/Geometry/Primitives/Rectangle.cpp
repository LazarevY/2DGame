#include "Rectangle.h"

Rectangle::Rectangle() : position(0,0),size(1,1)
{
}

Rectangle::Rectangle(const vector2 & position, const vector2 & size) :
						position(position), size(size)
{
}

 vector2 Rectangle::getPosition()const
{
	return position;
}

 vector2  Rectangle::getSize()const
{
	return size;
}

void Rectangle::setPosition(const vector2 & position)
{
	this->position = vector2(position);
}

void Rectangle::setSize(const vector2 & size)
{
	this->size = vector2(size);
}

vector2 Rectangle::getMin() const
{
	return position - size;
}

vector2 Rectangle::getMax() const
{
	return position + size;
}

Interval2D Rectangle::getIntervalX() const
{
	return Interval2D(getMin(), vector2(position.x + size.x, position.y - size.y));
}

Interval2D Rectangle::getIntervalY() const
{
	return Interval2D(getMin(), vector2(position.x - size.x, position.y +size.y));
}
