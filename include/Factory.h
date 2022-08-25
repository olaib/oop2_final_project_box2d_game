#pragma once

#include <Box2D/Box2D.h>
#include <memory>
#include <macros.hpp>
#include <exception>


// this is factory class a template class(design pattern) for creating objects
template <class T>
class Factory
{
public:
	Factory() = default;

	using funcPtr = std::unique_ptr<T>(*)(const sf::Vector2f&, b2World*);
	static std::unique_ptr<T> create(Type, const sf::Vector2f&, b2World*);
	static bool registerIt(Type, funcPtr);

private:
	//private functions:
	static auto& getMap()
	{
		static std::map<Type, funcPtr> map;
		return map;
	}
};

template <class T>
std::unique_ptr<T> Factory<T>::create(Type object, const sf::Vector2f& position, b2World* world)
{
	auto it = Factory<T>::getMap().find(object);
	if (it == Factory<T>::getMap().end())
	{
		return nullptr;
	}
	return it->second(position, world);
}

template <class T>
bool Factory<T>::registerIt(Type object, funcPtr func)
{
	Factory<T>::getMap().emplace(object, func);
	return true;
}