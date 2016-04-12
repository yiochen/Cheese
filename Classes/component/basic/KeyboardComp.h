#pragma once
#include "component/Component.h"
#include "entity/Entity.h"
//Keyboard component is basically a marker to say that this entity will be affected by keyboard. 
//the entity will be picked up by keyboard runner because it has this component. 
class KeyboardComp:public Comp {
public:
    KeyboardComp();
	//change the velocity of the entity
	void changeVel(Entity* entity);
	void resetVel(Entity* entity);
};
