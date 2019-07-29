#include "SpriteLoader.h"
#include <Engine/Components/Texture/Sprite.h>
#include <SOIL/SOIL.h>

SpriteLoader::SpriteLoader()
{
}

BaseResource * SpriteLoader::load_resource(const std::string & path)
{
	throw ResourceLoadingException(ResourceLoadingErrorType::UnresolvedFunction, "", __FILE__, __LINE__, __FUNCTION__);
}

BaseResource * SpriteLoader::load_resource(const std::string & path, std::optional<std::any> options)
{
	if(!options.has_value() || options.value().type() != typeid(uinfo_vector4))
	{
		throw ResourceLoadingException(ResourceLoadingErrorType::WrongOptionsData, "Invalid options type - excepted uinfo_vector4!",
			__FILE__, __LINE__, __FUNCTION__);
	}
	// This vector include info about this sprite states
	// value_1 - count width frames
	// value_2 - count height frames
	// value_3 - count frames(not value_1 * value_2!!)
	// value_4 - type texture data(usual RBG or RGBA)
	uinfo_vector4 info_vector4 = std::any_cast<uinfo_vector4>(options.value());

	unsigned int  load_type = info_vector4.value_4;
	unsigned int  format= info_vector4.value_4 == SOIL_LOAD_RGBA ? GL_RGBA : GL_RGB;
	unsigned int internalFormat = format == GL_RGBA ? GL_RGBA8 : GL_RGB8;
	int width, height, channels;


	unsigned char* image_data = SOIL_load_image(path.c_str(), &width, &height,&channels, load_type);
	// Clean error log
	glGetError();
	if(image_data == nullptr)
	{
		throw ResourceLoadingException(ResourceLoadingErrorType::ProblemFile, "", __FILE__, __LINE__, __FUNCTION__);
	}

	unsigned int width_frame = width/info_vector4.value_1;
	unsigned int height_frame = height/info_vector4.value_2;
	unsigned int count_frames = info_vector4.value_3;

	int mipLevelCount = 1;

	Sprite* sprite = new Sprite(width, height, width_frame, height_frame, count_frames);
	sprite->bindTexture();

	glTexStorage3D(GL_TEXTURE_2D_ARRAY, mipLevelCount, internalFormat, width_frame, height_frame, count_frames);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, width);

	int col_count = info_vector4.value_1;
	int row_count = info_vector4.value_2;
	for (int iRow = 0; iRow < row_count; ++iRow) {
		for (int iCol = 0; iCol < col_count; ++iCol) {
			glTexSubImage3D(
				GL_TEXTURE_2D_ARRAY, 0,
				0, 0, col_count * iRow + iCol,
				width_frame, height_frame, 1,
				format, GL_UNSIGNED_BYTE,
				image_data + (iRow * height_frame * width + iCol * width_frame) * channels);
		}
	}

	if(int e = glGetError() != GL_NO_ERROR)
	{
		throw ResourceLoadingException(ResourceLoadingErrorType::WrongOptionsData, "Invalid options data, gl_error_code - " + e,  __FILE__,
			__LINE__, __FUNCTION__);
	}

	return new Resource<Sprite>(sprite);
}
