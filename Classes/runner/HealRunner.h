#pragma once
#include "EntityRunner.h"
#include "entity/zombie/Zombie.h"
/*This runner will iterate over all healers and make them heal*/
class HealRunner:public EntityRunner {
private:
	void updateEntity(Zombie* entity, float delta);
public:
    HealRunner();
	void update(float delta) override;
};
