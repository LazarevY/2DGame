#pragma once

#include <Engine/Components/GL.h>
#include <Engine/Utils/types.h>

enum class ArrayBufferDataType
{
	StaticData = GL_STATIC_DRAW, DynamicData = GL_DYNAMIC_DRAW, StreamData = GL_STREAM_DRAW
};

enum class DrawDataMode
{
	Lines = GL_LINES, Triangles = GL_TRIANGLES, Points = GL_POINTS
};

enum class DrawDataType
{
	UnsignedInt = GL_UNSIGNED_INT
};

class ArrayBufferHandler
{
public:
	ArrayBufferHandler();
	ArrayBufferHandler(u_int dataSize, c_vec_f & data, ArrayBufferDataType dataType);
	~ArrayBufferHandler();

	void setArrayBufferData(u_int dataSize, c_vec_f& data, ArrayBufferDataType dataType);
	void setAttributes(u_int index, u_int size, GLenum type, GLboolean normalized, u_int stride,
		const GLvoid* pointer);
	void addElementBuffer();
	void setElementBufferData(u_int dataSize, c_vec_ui& data, ArrayBufferDataType dataType);

	void drawIndexData(DrawDataMode mode, GLsizei count, DrawDataType dataType, const GLvoid* indices) const;
	void drawArrayData(DrawDataMode mode, GLint first, GLsizei count) const;

	bool isIndexed() const;

	void bind_vbo() const;
	void bind_vao() const;
	void bind_ebo();
	
	void unbind_vbo();
	void unbind_vao() const;
	void unbind_ebo();
private:
	u_int id_vbo;
	u_int id_vao;
	u_int id_ebo;
};