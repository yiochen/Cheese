#pragma once
#include "component/CompHeader.h"
/*Used to make a player run off screen when he runs out of zombies*/
class EscapeComp :public Comp {
public:
	EscapeComp();

//	bool chase(Entity* self, Entity* target, float delta);
};
