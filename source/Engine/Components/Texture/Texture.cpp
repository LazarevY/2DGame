#include "Texture.h"
#include <iostream>

Texture::Texture()
{
	std::cout << "Texture called";
	glGenTextures(1, &texture_id);
}

Texture::~Texture()
{
	glDeleteTextures(1, &texture_id);
}

