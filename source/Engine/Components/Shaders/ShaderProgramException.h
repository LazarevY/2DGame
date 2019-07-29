#pragma once
#include <Engine/Components/Exceptions/BaseException.h>

class ShaderProgramException : public BaseExceprtion
{
public:
	ShaderProgramException(strconst& message, strconst& file, size_t line, strconst& function) :
		BaseExceprtion(message, file, line, function)
	{

	};
	~ShaderProgramException() {};
};