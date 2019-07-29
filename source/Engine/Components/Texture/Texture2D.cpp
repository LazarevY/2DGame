#include "Texture2D.h"


Texture2D::Texture2D(int width, int height) : width(width), height(height)
{

}

Texture2D::~Texture2D() 
{

}

void Texture2D::setWrapMode(WrapMode mode)
{
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLint>(mode));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLint>(mode));
}

void Texture2D::setMagFiltering(FilteringType type)
{
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(type));
}

void Texture2D::setMinFiltering(FilteringType type)
{
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(type));
}

void Texture2D::bindTexture() const
{
	glBindTexture(GL_TEXTURE_2D, texture_id);
}

void Texture2D::unbindTexture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int Texture2D::getWidth()
{
	return width;
}

unsigned int Texture2D::getHeight()
{
	return height;
}
