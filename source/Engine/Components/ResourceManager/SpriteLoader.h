#pragma once

#include "ResourceLoader.h"
#include <Engine/Utils/info_vector.h>

class SpriteLoader : public ResourceLoader
{
public:
	SpriteLoader();
	~SpriteLoader() = default;

	BaseResource* load_resource(const std::string& path) override;
	BaseResource* load_resource(const std::string& path, std::optional<std::any> options) override;
};