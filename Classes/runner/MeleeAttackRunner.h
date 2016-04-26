#pragma once
#include "entity/Entity.h"
#include "EntityRunner.h"
class MeleeAttackRunner : public EntityRunner{
private:
	void updateEntity(Entity* entity, float delta);
public:
    MeleeAttackRunner();
	void update(float delta) override;
	
};
