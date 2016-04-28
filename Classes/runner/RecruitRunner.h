#pragma once
#include "EntityRunner.h"
#include "entity/Entity.h"
#include "entity/zombie/Zombie.h"
/*This is for player(swiss) to recruit zombies)*/
class RecruitRunner: public EntityRunner {
public:
    RecruitRunner();
	void update(float delta) override;
	void updateEntity(Zombie* entity, float delta);
};
