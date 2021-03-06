#pragma once
#include <Engine/Utils/types.h>
class Rectangle
{
public:
	Rectangle();
	Rectangle(const vector2 &position, const vector2 &size);
	~Rectangle() = default;

	vector2 getPosition() const;
	void setPosition(const vector2 &position);

	vector2 getSize() const;
	void setSize(const vector2 &size);

	vector2 getMin() const;
	vector2 getMax() const;
private:
	vector2 position;
	vector2 size; // HALF-SIZE
};