#pragma once
#include <Engine/Utils/types.h>

class  OrientedRectangle
{
public:
	OrientedRectangle();
	OrientedRectangle(float rotation, const vector2& position, const vector2& size);

	float getRotation() const;
	void setRotation(float rotation);

	vector2 getPosition() const;
	void setPosition(const vector2 &position);

	vector2 getSize() const;
	void setSize(const vector2 &size);
private:
	float rotation;
	vector2 position;
	vector2 size; // HALF-SIZE
};