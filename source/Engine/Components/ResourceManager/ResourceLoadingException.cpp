#include "ResourceLoadingException.h"

ResourceLoadingException::ResourceLoadingException(ResourceLoadingErrorType error, strconst message, strconst file, size_t line, strconst function):	
BaseExceprtion(message, file, line, function), error(error)
{
}

 std::unordered_map<ResourceLoadingErrorType, const char*> ResourceLoadingException::errors_map = {
		{ResourceLoadingErrorType::InvalidData, "Invalid data. Check it."},
		{ResourceLoadingErrorType::ProblemFile, "File couldn't be open or damaged, or include errors."},
		{ResourceLoadingErrorType::UnknowLoadingFormat, "No loader found for the specified resource."},
		{ResourceLoadingErrorType::UnresolvedFunction, "This function cannot be used in this loader."},
		{ResourceLoadingErrorType::WrongOptionsData, "Additional parameters are of the wrong type or contain incorrect values."}
 };

