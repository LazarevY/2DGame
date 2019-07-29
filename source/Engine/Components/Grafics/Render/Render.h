#pragma once
#include <Engine/Components/Shaders/ShaderProgram.h>
#include <Engine/Components/Buffers/ArrayBufferHandler.h>
#include <Engine/Components/Texture/Texture.h>
#include <Engine/Utils/types.h>
class Render
{
public:
	Render(ShaderProgram* shader);
	virtual ~Render() = default;

protected:
	ShaderProgram* shader;

	virtual void initUniformVariables() =0;
};