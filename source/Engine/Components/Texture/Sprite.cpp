#include "Sprite.h"

Sprite::Sprite(unsigned int texture_width, unsigned int texture_height, unsigned int frame_width, unsigned int frame_height, int count_frames) :
	Texture(), texture_width(texture_width), texture_height(texture_height), frame_width(frame_width), frame_height(frame_height),count_frames(count_frames)
{
}

void Sprite::bindTexture() const
{
	glBindTexture(GL_TEXTURE_2D_ARRAY, texture_id);
}

void Sprite::unbindTexture()
{
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

void Sprite::setWrapMode(WrapMode mode)
{
	glBindTexture(GL_TEXTURE_2D_ARRAY, texture_id);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, static_cast<GLint>(mode));
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, static_cast<GLint>(mode));
}

void Sprite::setMagFiltering(FilteringType type)
{
	glBindTexture(GL_TEXTURE_2D_ARRAY, texture_id);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(type));
}

void Sprite::setMinFiltering(FilteringType type)
{
	glBindTexture(GL_TEXTURE_2D_ARRAY, texture_id);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(type));
}

unsigned Sprite::getTextureWidth()
{
	return texture_width;
}

unsigned Sprite::getTextureHeight()
{
	return texture_height;
}

unsigned Sprite::getTextureFrameWidth()
{
	return frame_width;
}

unsigned Sprite::getTextureFrameHeight()
{
	return frame_height;
}

int Sprite::getCountFrames()
{
	return count_frames;
}
