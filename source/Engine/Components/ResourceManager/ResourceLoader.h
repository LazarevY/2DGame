#ifndef RESOURCE_LOADER_H
#define RESOURCE_LOADER_H


#include <string>
#include <optional>
#include <any>

#include "Resource.h"
#include "ResourceLoadingException.h"
class ResourceLoader
{
public:
	ResourceLoader() {};
	virtual ~ResourceLoader() = default;
	virtual BaseResource* load_resource(const std::string & path) = 0;
	virtual BaseResource* load_resource(const std::string & path, std::optional<std::any> options) = 0;
};

#endif // RESOURCE_LOADER_H
