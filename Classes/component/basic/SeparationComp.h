#pragma once
#include "component/CompHeader.h"
/*Zombie or entities with this component should try to Separate from a Vec2 position.
This is a marker component for runner to recognize the entity*/
class SeparationComp:public Comp {
public:
    SeparationComp();
	/*Helper function to make the entity stay away from the target by modifying it's speed,
	the entity further away from the target will receive less influence*/
	void separate(Entity* entity, Vec2 target, float delta);
};
