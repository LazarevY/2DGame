#pragma once
#include <Engine/Components/Exceptions/BaseException.h>

enum class ArrayBufferError
{
	NoCreatedBuffer
};

class ArrayBufferException : public BaseExceprtion
{
public:
	ArrayBufferException(ArrayBufferError error, strconst& message, strconst& file, size_t line, strconst& function) :
		BaseExceprtion(message, file, line, function), error(error) {}
private:
	ArrayBufferError error;
};