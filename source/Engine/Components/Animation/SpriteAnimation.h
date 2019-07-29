#pragma once
#include "Animation.h"
#include <Engine/Components/Texture/Sprite.h>
class SpriteAnimation : public Animation
{
public:
	SpriteAnimation(Sprite* source);
	~SpriteAnimation() override;

	
	int getCurrentFrameNumber() const;
	void setCurrentFrameNumber(int number);

	// Отражение по оси Х, при отрисовке текстура будет отражена по оси Х если включена эта опция
	bool isXReflection() const;
	void enableXReflection();
	void disableXReflection();

	void bindSource() const;
	void unbindSource() const;

	int getCountFrames() const;

private:
	Sprite* sprite_source;

	int row_frame_count;
	int col_frame_count;
	int current_number_frame;

	bool x_reflection;
};