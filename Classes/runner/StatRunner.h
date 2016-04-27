#pragma once
#include "EntityRunner.h"
#include "entity/Entity.h"
/*This runner is in charge of finallizing the states of the entity in each frame(e.g. HP). The entity should have combatComp.
*/
class StatRunner:public EntityRunner {
public:
    StatRunner();
	void update(float delta) override;
	void updateEntity(Entity* entity, float delta);

};
