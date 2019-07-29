#ifndef TEXTURE_H
#define TEXTURE_H
#include <Engine/Components/GL.h>
#include "Texture.h"
class  Texture2D : public Texture
{
public:
	Texture2D(int width = 0, int height = 0);
	~Texture2D();
				
	void setWrapMode(WrapMode mode) override;
	void setMagFiltering(FilteringType type) override;
	void setMinFiltering(FilteringType type) override;

	void bindTexture() const override;
	void unbindTexture() override;

	unsigned int getWidth();
	unsigned int getHeight();

private:
	unsigned int width;
	unsigned int height;
};

#endif // TEXTURE_H
