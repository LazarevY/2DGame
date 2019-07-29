#include "SpriteAnimator.h"

void SpriteAnimator::start(float current_time)
{
	inAnimate = true;
	animation->setCurrentFrameNumber(0);
	nextFrameTime = current_time + animation_time;
}

void SpriteAnimator::animate(float current_time)
{
	if(inAnimate && current_time >= nextFrameTime)
	{
		int current_frame = animation->getCurrentFrameNumber();
		if(current_frame == animation->getCountFrames() - 1)
		{
			animation->setCurrentFrameNumber(0);
		}
		else
		{
			animation->setCurrentFrameNumber(++current_frame);
		}
		nextFrameTime += animation_time;
	}
}
