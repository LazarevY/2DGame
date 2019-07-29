#pragma once
#include <exception>
#include <string>

using strconst = const std::string;

class BaseExceprtion : std::exception
{
public:
	BaseExceprtion(strconst& message, strconst& file, size_t line, strconst& function) :
		message(message), file(file), line(line), function(function) {}
	~BaseExceprtion() = default;
	const char* getMessage()
	{
		return message.c_str();
	}

	const char* getFille()
	{
		return file.c_str();
	}

	const size_t getLine()
	{
		return line;
	}

	const char* getFunction()
	{
		return function.c_str();
	}

protected:
	strconst message;
	size_t line;
	strconst file;
	strconst function;
};
