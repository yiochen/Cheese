#pragma once
#include "EntityRunner.h"
#include "entity/Entity.h"
/*This runner will go through all the ActionFlagComp and reduce the timer s*/
class ActionFlagRunner : public EntityRunner{
public:
    ActionFlagRunner();
	void update(float delta) override;
	void updateEntity(Entity* entity, float delta);
};
