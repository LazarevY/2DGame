#pragma once

#include "Render.h"
#include <Engine/Components/Animation/SpriteAnimation.h>

class SpriteAnimationRender : public Render
{
public:
	SpriteAnimationRender(ShaderProgram* shader);

	void render(const ArrayBufferHandler& buffer, const SpriteAnimation& animation, const matrix3& model,
		const matrix3& view, const matrix3& projection) const;
private:
	void initUniformVariables() override;
};