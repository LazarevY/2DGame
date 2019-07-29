#pragma once

#include <Engine/Utils/types.h>

class Camera2D
{
public:

	Camera2D(const vector2& position, float zoom, float extent_x, float extent_y, float world_unit);
	~Camera2D() = default;

	vector2 getPosition() const;
	void setPosition(const vector2& position);

	double getZoom();
	void setZoom(double zoom);

	matrix4 getViewMatrix() const;
	matrix4 getProjectionMatrix() const;

private:
	vector2 position;
	float zoom;

	float extent_x;
	float extent_y;

	const float world_unit;
};