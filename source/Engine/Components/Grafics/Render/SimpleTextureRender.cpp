#include "SimpleTextureRender.h"

SimpleTextureRender::SimpleTextureRender(ShaderProgram* shader) : Render(shader)
{
	SimpleTextureRender::initUniformVariables();
}

void SimpleTextureRender::render(const ArrayBufferHandler& buffer, const Texture& texture, matrix4 model,
	matrix4 proj_view)
{	
	shader->useProgram();
	this->shader->setUniformParameter("model", model);
	this->shader->setUniformParameter("proj_view", proj_view);
	texture.bindTexture();
	if(buffer.isIndexed())
	{
		buffer.drawIndexData(DrawDataMode::Triangles, 6, DrawDataType::UnsignedInt, 0);
	}
	//buffer.drawVertexData();
}

void SimpleTextureRender::initUniformVariables()
{
	shader->setUniformId("model");
	shader->setUniformId("proj_view");
}
