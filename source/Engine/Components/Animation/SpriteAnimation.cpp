#include "SpriteAnimation.h"

SpriteAnimation::SpriteAnimation(Sprite * source) :
	sprite_source(source), current_number_frame(0), x_reflection(false)
{
	row_frame_count = source->getTextureWidth() / source->getTextureFrameWidth();
	col_frame_count = source->getTextureHeight() / source->getTextureFrameHeight();
}

SpriteAnimation::~SpriteAnimation()
{
}

void SpriteAnimation::setCurrentFrameNumber(int number)
{
	current_number_frame = number;
}

bool SpriteAnimation::isXReflection() const
{
	return x_reflection;
}

void SpriteAnimation::enableXReflection()
{
	x_reflection = true;
}

void SpriteAnimation::disableXReflection()
{
	x_reflection = false;
}

int SpriteAnimation::getCurrentFrameNumber() const
{
	return current_number_frame;
}

void SpriteAnimation::bindSource() const
{
	sprite_source->bindTexture();
}

void SpriteAnimation::unbindSource() const
{
	sprite_source->unbindTexture();
}

int SpriteAnimation::getCountFrames() const
{
	return sprite_source->getCountFrames();
}


