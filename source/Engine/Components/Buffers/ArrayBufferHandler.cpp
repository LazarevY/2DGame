#include "ArrayBufferHandler.h"
#include "ArrayBufferException.h"
#include <iostream>

ArrayBufferHandler::ArrayBufferHandler()
{
	glGenBuffers(1, &id_vbo);
	glGenVertexArrays(1, &id_vao);
	id_ebo = 0;
}

ArrayBufferHandler::ArrayBufferHandler(u_int dataSize, c_vec_f & data, ArrayBufferDataType dataType)
{
	glGenBuffers(1, &id_vbo);
	glGenVertexArrays(1, &id_vao);
	id_ebo = 0;

	glBindVertexArray(id_vao);;
	glBindBuffer(GL_ARRAY_BUFFER, id_vbo);
	//TODO : last param should been set!
	glBufferData(GL_ARRAY_BUFFER, dataSize, data.data(), static_cast<u_int>(dataType));
	glBindVertexArray(0);
}

ArrayBufferHandler::~ArrayBufferHandler()
{
	glDeleteBuffers(1, &id_vao);
	glDeleteBuffers(1, &id_vbo);
	glDeleteBuffers(1, &id_ebo);
}

void ArrayBufferHandler::setArrayBufferData(u_int dataSize, c_vec_f& data, ArrayBufferDataType dataType)
{
	glBindVertexArray(id_vao);
	glBufferData(GL_ARRAY_BUFFER, dataSize, data.data(), static_cast<u_int>(dataType));
	glBindVertexArray(0);
}

void ArrayBufferHandler::setAttributes(u_int index, u_int size, GLenum type, GLboolean normalized, u_int stride,
	const GLvoid* pointer)
{
	glBindVertexArray(id_vao);
	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	glEnableVertexAttribArray(index);
	glBindVertexArray(0);
}

void ArrayBufferHandler::addElementBuffer()
{
	if (!id_ebo)
	{
		glGenBuffers(1, &id_ebo);
	}
}

void ArrayBufferHandler::setElementBufferData(u_int dataSize, c_vec_ui& data, ArrayBufferDataType dataType)
{
	try {
		if (!id_ebo)
		{
			throw ArrayBufferException(ArrayBufferError::NoCreatedBuffer, "Element buffer doesn't create!", __FILE__, __LINE__,
				__FUNCTION__);
		}
	}
	catch (ArrayBufferException& exception)
	{
		std::cerr << "Exception - " << exception.getMessage() << "\nFile - " << exception.getFille() <<
			"\nLine - " << exception.getLine() << "\nFunction - " << exception.getFunction() << std::endl;
		system("pause");
	}
	glBindVertexArray(id_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataSize, data.data(), static_cast<u_int>(dataType));
	glBindVertexArray(0);
}

void ArrayBufferHandler::drawIndexData(DrawDataMode mode, GLsizei count, DrawDataType dataType, const GLvoid* indices) const
{
	glBindVertexArray(id_vao);
	glDrawElements(static_cast<u_int>(mode), count, static_cast<u_int>(dataType), indices);
	glBindVertexArray(0);
}

void ArrayBufferHandler::drawArrayData(DrawDataMode mode, GLint first, GLsizei count) const
{
	glDrawArrays(static_cast<u_int>(mode), first, count);
}

bool ArrayBufferHandler::isIndexed() const
{
	return id_ebo;
}

void ArrayBufferHandler::bind_vbo() const
{
	glBindBuffer(GL_ARRAY_BUFFER, id_vbo);
}

void ArrayBufferHandler::bind_vao() const
{
	glBindVertexArray(id_vao);
}

void ArrayBufferHandler::bind_ebo()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_ebo);
}

void ArrayBufferHandler::unbind_vbo()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ArrayBufferHandler::unbind_vao() const
{
	glBindVertexArray(0);
}

void ArrayBufferHandler::unbind_ebo()
{
	if (!id_ebo)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_ebo);
	}
}
