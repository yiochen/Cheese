#pragma once
#include "runner/EntityRunner.h"
#include "entity/Entity.h"
#include "entity/zombie/Zombie.h"
#include "entity/Item/Item.h"

class RangeAttackRunner : public EntityRunner{
public:
    RangeAttackRunner();
	void update(float delta) override;
	void updateEntity(Zombie* entity, float delta);
};
