#pragma once

#include "Render.h"

class SimpleTextureRender : public Render
{
public:
	
	SimpleTextureRender(ShaderProgram* shader);


	void render(const ArrayBufferHandler& buffer, const Texture& texture, matrix4 model, matrix4 proj_view);

private:
	void initUniformVariables() override;
};