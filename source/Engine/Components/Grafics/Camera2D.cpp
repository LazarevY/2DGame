#include "Camera2D.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/detail/_vectorize.hpp>

Camera2D::Camera2D(const vector2 & position, float zoom, float extent_x, float extent_y, float world_unit) :
	position(position),  zoom(zoom), extent_x(extent_x), extent_y(extent_y), world_unit(world_unit)
{
}

vector2 Camera2D::getPosition() const
{
	return position;
}

void Camera2D::setPosition(const vector2 & position)
{
	this->position = vector2(position);
}

double Camera2D::getZoom()
{
	return zoom;
}

void Camera2D::setZoom(double zoom)
{
	this->zoom = zoom;
}

matrix4 Camera2D::getViewMatrix() const
{
	
	return glm::translate(matrix4(), -vector3(position.x, position.y, 0));
}

matrix4 Camera2D::getProjectionMatrix() const
{
	const float x = extent_x * zoom;
	const float y = extent_y * zoom;
	return glm::ortho(-x, x, -y, y,-1.f,1.f);
}
