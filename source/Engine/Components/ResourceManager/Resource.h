#ifndef RESOURCE_H
#define RESOURCE_H
#include "BaseResource.h"

template<class T>
class Resource: public BaseResource
{
public:
    ~Resource() override;

	Resource(T* resource_data);
    T* getDataPtr();
protected:
	T* resource_data;
};

template <class T>
inline Resource<T>::Resource(T* resource_data) : resource_data(resource_data), BaseResource()
{

};
template<class T>
inline Resource<T>::~Resource()
{
	delete resource_data;
}

template <class T>
inline T* Resource<T>::getDataPtr()
{
	return resource_data;
}
#endif 
