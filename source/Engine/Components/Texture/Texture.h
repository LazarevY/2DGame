#pragma once

#include <Engine/Components/GL.h>
#include <SOIL/SOIL.h>
class Texture
{
public:
	enum class TexturePixelData
	{
		Load_RGB = SOIL_LOAD_RGB, Load_RGBA = SOIL_LOAD_RGBA
	};

	enum class FilteringType {
		Linear = GL_LINEAR, Nearest = GL_NEAREST, LinearMipmapLinear = GL_LINEAR_MIPMAP_LINEAR
	};

	enum class WrapMode
	{
		ClampToEdge = GL_CLAMP_TO_EDGE, Repeat = GL_REPEAT
	};

	Texture();
	virtual ~Texture();
	virtual void bindTexture() const = 0;
	virtual void unbindTexture() = 0;
	virtual void setWrapMode(WrapMode mode) = 0;
	virtual void setMagFiltering(FilteringType type)= 0;
	virtual void setMinFiltering(FilteringType type) = 0;

protected:
	unsigned int texture_id;
};