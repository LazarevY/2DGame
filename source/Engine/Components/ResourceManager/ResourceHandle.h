#pragma once
#include <Engine/Components/ResourceManager/Resource.h>
template<class T>
class ResourceHandle
{
public:
	ResourceHandle(Resource<T>* resource) : resource_data(resource){}


	T* getSourcePtr()
	{
		return resource_data->getDataPtr();
	}
private:
	Resource<T> *resource_data;
};

