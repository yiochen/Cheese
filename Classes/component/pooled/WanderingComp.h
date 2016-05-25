#pragma once
#include "component/CompHeader.h"
#include "entity/Entity.h"

USING_NS_CC;

/*
compnent used to determin where this zombie will wander to next*/

class WanderingComp : public PooledComp {
public:
	Vec2 target;
	void init();
	WanderingComp();
	~WanderingComp();
	void newTarget();
	bool arrived(Entity* entity);
	bool isChasing;
};