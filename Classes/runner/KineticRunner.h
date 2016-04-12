#pragma once
#include "EntityRunner.h"
#include "entity/Entity.h"

//The purpose of kinetic runner is simply update the current position base on the current velocity. 
//all other interaction should be done in other runners.
class KineticRunner :public EntityRunner {
public:
	KineticRunner();
	void update(float delta) override;
	void updateEntity(Entity* entity, float delta);
};
