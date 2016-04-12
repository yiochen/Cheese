#pragma once
#include "component/PooledComponent.h"
#include "cocos2d.h"
#include "entity/Entity.h"

USING_NS_CC;

class KineticComp :public PooledComp{	
public:
	Vec2 pos;
	Vec2 vel;
	Vec2 acc;
	float maxSpeed;
	bool resting;
    KineticComp();
	void step(Entity* ent);
	void stepZ(Entity* ent);
	void setPos(float, float);
	void setSpritePos(Entity* entity);
};
