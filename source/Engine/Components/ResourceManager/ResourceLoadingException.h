#pragma once
#include "Engine/Components/Exceptions/BaseException.h"
#include <unordered_map>
#include <sstream>

enum class ResourceLoadingErrorType
{
	ProblemFile, InvalidData, WrongOptionsData, UnknowLoadingFormat, UnresolvedFunction
};

class ResourceLoadingException : public BaseExceprtion
{

public:

	ResourceLoadingException(ResourceLoadingErrorType error, strconst message, strconst file, size_t line, strconst function);
	~ResourceLoadingException() = default;

	const ResourceLoadingErrorType getError()
	{
		return error;
	}

	std::string getExceptionLog()
	{
		std::ostringstream log;
		log << errors_map[error] << std::endl
			<< message << std::endl
			<< file << std::endl
			<< line << std::endl
			<< function << std::endl;
		return log.str();
	}

	const char* getFunction()
	{
		return function.c_str();
	}

private:
	ResourceLoadingErrorType error;

	static  std::unordered_map<ResourceLoadingErrorType, const char* > errors_map;
};
