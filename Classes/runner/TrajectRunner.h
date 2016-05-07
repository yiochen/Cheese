#pragma once
#include "runner/EntityRunner.h"
#include "entity/Entity.h"

/*This runner will update the position of the entity with TrajectComp, this is a similar runner as Kinetic Runner*/
class TrajectRunner:public EntityRunner {
public:
    TrajectRunner();
	void update(float delta) override;
	void updateEntity(Entity* entity, float delta);
};
