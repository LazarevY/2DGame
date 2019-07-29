#pragma once
#include  "Animator.h"
#include "SpriteAnimation.h"

class SpriteAnimator : public Animator
{
public:
	SpriteAnimator(SpriteAnimation* animation, float animation_time) : animation(animation), animation_time(animation_time)
	{
		inAnimate = false;
	};
	~SpriteAnimator() = default;

	void start(float current_time);
	void animate(float current_time);
private:
	float animation_time;
	bool inAnimate;
	float nextFrameTime;
	SpriteAnimation* animation;
};