#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include "ResourceLoader.h"
//#include <SOIL/SOIL.h>
class TextureLoader : public ResourceLoader
{
public:
	TextureLoader() {};
	~TextureLoader() = default;
	BaseResource* load_resource(const std::string& path) override;
	BaseResource* load_resource(const std::string& path, std::optional<std::any> options) override;
};

#endif // TEXTURELOADER_H
