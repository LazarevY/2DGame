#pragma once
#include "ResourceLoader.h"
#include <Engine/Components/Shaders/ShaderProgram.h>

class ShaderProgramLoader : public ResourceLoader
{
public:
	ShaderProgramLoader() {};
	~ShaderProgramLoader() = default;

	BaseResource* load_resource(const std::string& path) override;
	BaseResource* load_resource(const std::string& path, std::optional<std::any> options) override;
};