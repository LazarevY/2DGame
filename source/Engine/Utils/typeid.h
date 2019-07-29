#pragma once
#include <typeindex>
using Typeid = std::type_index;

template<class T>
Typeid getClassType()
{
	return std::type_index(typeid(T));
}