#pragma once
#include "component/PooledComponent.h"
#include "cocos2d.h"
#include "entity/Entity.h"

USING_NS_CC;

/*Kinetic component store the information about entity's velocity and speed. 
It provides a helper function to update the position of base on the current velocity.
*/
class KineticComp :public PooledComp{	
public:
	//pos is the world position
	//TODO: right now the position is relative to the window, to be change to world coordinate later. 
	Vec2 pos;
	Vec2 vel;
	Vec2 acc;
	float maxSpeed;
	bool resting;
    KineticComp();
	void step(Entity* ent, float delta);
	//void stepZ(Entity* ent);
	void setPos(float, float);
	void setSpritePos(Entity* entity);
	~KineticComp() {}
};
