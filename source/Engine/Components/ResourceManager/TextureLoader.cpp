#include "TextureLoader.h"
#include <Engine/Components/Texture/Texture2D.h>
#include <iostream>

BaseResource * TextureLoader::load_resource(const std::string & path)
{
	return load_resource(path, Texture::TexturePixelData::Load_RGB);
}

BaseResource * TextureLoader::load_resource(const std::string & path, std::optional<std::any> options)
{
	if (!options.has_value() || options.value().type() != typeid(Texture::TexturePixelData))
	{
		throw ResourceLoadingException(ResourceLoadingErrorType::WrongOptionsData, "", __FILE__, __LINE__, __FUNCTION__);
	}
	int width, height;
	int load_type = static_cast<int>(std::any_cast<Texture::TexturePixelData>(options.value()));

	unsigned char* image = SOIL_load_image(path.c_str(), &width, &height, 0, load_type);
	Texture2D* texture = new Texture2D(width, height);

	texture->bindTexture();

	GLint format = load_type == SOIL_LOAD_RGBA ? GL_RGBA : GL_RGB;

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0,
		format, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image);
	texture->unbindTexture();

	return new Resource<Texture2D>(texture);
}
