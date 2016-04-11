#pragma once
#include "component/PooledComponent.h"
#include "cocos2d.h"

USING_NS_CC;

class KineticComp :public PooledComp{	
public:
	Vec2 pos;
	Vec2 vel;
	Vec2 acc;
	float maxSpeed;
    KineticComp();
};