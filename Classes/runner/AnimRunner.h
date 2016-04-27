#pragma once
#include "runner/EntityRunner.h"
#include "entity/Entity.h"
//AnimRunner will update the animation of the entity if the entity has KINETIC COMPONENT and AnimComp
//Note that KineticComp is essential for determine the location of the sprite. 
//AnimRunner should be the last runner running, because it is also in charged of removing the entity from the gameworld;
class AnimRunner:public EntityRunner {
private:
	bool runAnimRunner(Entity* entity);
public:
    AnimRunner();
	void update(float delat) override;

};
