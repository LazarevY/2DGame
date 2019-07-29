#pragma once

#include "Texture.h"

class Sprite : public Texture
{
public:
	Sprite(unsigned int texture_width, unsigned int texture_height, unsigned int frame_width, unsigned int frame_height, int count_frames);
	~Sprite() = default;

	void bindTexture() const override;
	void unbindTexture() override;

	void setWrapMode(WrapMode mode) override;
	void setMagFiltering(FilteringType type) override;
	void setMinFiltering(FilteringType type) override;

	unsigned int getTextureWidth();
	unsigned int getTextureHeight();

	unsigned int getTextureFrameWidth();
	unsigned int getTextureFrameHeight();

	int getCountFrames();
	   
private:
	unsigned int texture_width;
	unsigned int texture_height;

	unsigned int frame_width;
	unsigned int frame_height;
	int count_frames;
};