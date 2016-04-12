#pragma once
#include "component/Component.h"
#include "entity/Entity.h"
class KeyboardComp:public Comp {
public:
    KeyboardComp();
	//change the velocity of the entity
	void changeVel(Entity* entity);
	void resetVel(Entity* entity);
};
