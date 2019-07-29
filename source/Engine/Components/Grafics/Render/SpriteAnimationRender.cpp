#include "SpriteAnimationRender.h"

SpriteAnimationRender::SpriteAnimationRender(ShaderProgram* shader) : Render(shader)
{
	SpriteAnimationRender::initUniformVariables();
}

void SpriteAnimationRender::render(const ArrayBufferHandler & buffer, const SpriteAnimation & animation, const matrix3 & model, const matrix3 & view, const matrix3 & projection) const
{
	shader->useProgram();
	shader->setUniformParameter("model", glm::inverse(projection) * model);
	shader->setUniformParameter("proj_view", projection * view);
	shader->setUniformParameter("layer", animation.getCurrentFrameNumber());
	shader->setUniformParameter("x_reflection", animation.isXReflection());
	animation.bindSource();
	if (buffer.isIndexed())
		buffer.drawIndexData(DrawDataMode::Triangles, 6, DrawDataType::UnsignedInt, 0);
	else 
		buffer.drawArrayData(DrawDataMode::Triangles, 0, 6);
}

void SpriteAnimationRender::initUniformVariables()
{
	shader->setUniformId("model");
	shader->setUniformId("proj_view");
	shader->setUniformId("layer");
	shader->setUniformId("x_reflection");
}
