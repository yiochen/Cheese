#pragma once
#include "component/CompHeader.h"
/*Zombie or entities with this component should try to seperate from a Vec2 position.
This is a marker component for runner to recognize the entity*/
class SeperationComp:public Comp {
public:
    SeperationComp();
	/*Helper function to make the entity stay away from the target by modifying it's speed,
	the entity further away from the target will receive less influence*/
	void seperate(Entity* entity, Vec2 target, float delta);
};
