#pragma once
#include <unordered_map>
#include "component/ComponentCatalog.h"
#include "component/Component.h"
#include "component/PooledComponent.h"
/*
*	Entity is an abstract class
*/
class Entity {
public:
	std::unordered_map<COMP_CA, Comp*> components;
	//std::unordered_map<COMP_CA, PooledComp*> pooledComponents;
	virtual void init() {};//the default entity init function doesn't do anything
    Entity();
};
