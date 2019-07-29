#include "OrientedRectangle.h"

OrientedRectangle::OrientedRectangle() : rotation(0.0f), position(0,0), size(1,1)
{
}

OrientedRectangle::OrientedRectangle(float rotation, const vector2& position, const vector2& size) :
	rotation(rotation), position(	position), size(size)
{
}

float OrientedRectangle::getRotation() const
{
	return rotation;
}

void OrientedRectangle::setRotation(float rotation)
{
	this->rotation = rotation;
}

vector2 OrientedRectangle::getPosition() const
{
	return position;
}

void OrientedRectangle::setPosition(const vector2 & position)
{
	this->position = vector2(position);
}

vector2 OrientedRectangle::getSize() const
{
	return size;
}

void OrientedRectangle::setSize(const vector2 & size)
{
	this->size = vector2(size);
}
