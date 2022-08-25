#pragma once
#include "Object/Object.h"
#include <typeinfo>
#include <typeindex>
#include <unordered_map>

using HitFunctionPtr = void (*)(Object*, Object*);
using _Key = std::pair<std::type_index, std::type_index>;
using HitTable = std::map<_Key, HitFunctionPtr>;

// Sample struct for exception throwing
struct UnknownCollision : public std::runtime_error
{
	UnknownCollision(Object& a, Object& b)
		: std::runtime_error(std::string("Unknown collision of ") + typeid(a).name() + " and " + typeid(b).name())
	{}
};

void processCollision(Object*, Object*);