#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <unordered_map>
#include <optional>
#include <any>
#include <filesystem>

#include <Engine/Utils/typeid.h>
#include <Engine/Components/ResourceManager/ResourceLoader.h>
#include <Engine/Components/ResourceManager/ResourceHandle.h>
#include <iostream>

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();
	template<class L>
	void register_resource_loader(ResourceLoader* loader);

	template<class L>
	void unregister_resource_loader();

	template<class R>
	ResourceHandle<R>* load_resource(const std::string& path);

	template<class R>
	ResourceHandle<R>* load_resource(const std::string& path, const std::string& id);
	
	template<class R>
	ResourceHandle<R>* load_resource(const std::string& path, std::optional<std::any> options);

	template<class R>
	ResourceHandle<R>* load_resource(const std::string& path, const std::string& id, std::optional<std::any> options);

	//TODO : add implementation!
	template <class R>
	ResourceHandle<R> getResource(const std::string& id);
private:
	std::unordered_map<std::type_index, ResourceLoader*> loader_list;
	std::unordered_map<std::string, BaseResource*> resources_list;
};

template<class L>
void ResourceManager::register_resource_loader(ResourceLoader * loader)
{
	loader_list.insert({getClassType<L>(), loader});
}

template<class L>
void ResourceManager::unregister_resource_loader()
{
	loader_list.erase(getClassType<L>());
}

template<class R>
ResourceHandle<R>* ResourceManager::load_resource(const std::string & path)
{
	return load_resource<R>(path, path, std::optional<std::any>());
}

template<class R>
ResourceHandle<R>* ResourceManager::load_resource(const std::string & path, const std::string & id)
{	
	return load_resource<R>(path, id, std::optional<std::any>());
}

template <class R>
ResourceHandle<R>* ResourceManager::load_resource(const std::string& path, std::optional<std::any> options)
{
	return load_resource<R>(path, path, options);
}

template <class R>
ResourceHandle<R>* ResourceManager::load_resource(const std::string& path, const std::string& id, std::optional<std::any> options)
{
	try
	{
	//TODO : add exceptions!!
	if(!std::filesystem::exists(path))
	{
		throw ResourceLoadingException(ResourceLoadingErrorType::ProblemFile, "File doesn't exist", __FILE__, __LINE__, __FUNCTION__);
	}
	ResourceLoader* loader = loader_list.at(getClassType<R>());
	if (loader == nullptr)
	{
		throw ResourceLoadingException(ResourceLoadingErrorType::UnknowLoadingFormat, "", __FILE__, __LINE__, __FUNCTION__);
	}


		BaseResource* resource = loader->load_resource(path, options);
		resources_list.insert({id, resource});
		return new ResourceHandle<R>(dynamic_cast<Resource<R>*>(resource));
	}catch(ResourceLoadingException &exception)
	{
		std::cerr << exception.getExceptionLog();
		system("pause");
		return nullptr;
		//exit(-1);
	}
	
	
}

template<class R>
inline ResourceHandle<R> ResourceManager::getResource(const std::string& id)
{
	auto resource_cell = resources_list.find(id);

	if(resource_cell == resources_list.end())
	{
		return  ResourceHandle<R>(nullptr);
	}

	Resource<R>* resource = dynamic_cast<Resource<R>*>(resource_cell->second);
	return  ResourceHandle<R>(resource);
}

#endif // RESOURCE_MANAGER_H


