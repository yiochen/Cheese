#pragma once
#include "entity/Entity.h"
#include "EntityRunner.h"

/*
used to update where the target is wandering to*/
class WandererRunner : public EntityRunner {
public:
	WandererRunner();
	void updateEntity(Entity*, float);
	void update(float);

};