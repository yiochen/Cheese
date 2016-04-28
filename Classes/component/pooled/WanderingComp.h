#pragma once
#include "component/CompHeader.h"

USING_NS_CC;

/*
compnent used to determin where this zombie will wander to next*/

class WanderingComp : public PooledComp {
public:
	Vec2 target;
	WanderingComp();
	~WanderingComp();
	void newTarget();
	bool isChasing;
};