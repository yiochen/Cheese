#pragma once
#include "EntityRunner.h"
#include "entity/Entity.h"
#include "entity/zombie/Zombie.h"

/*This runner is in charge of modifying zombies' velocity. */
class ZombieFollowRunner :public EntityRunner{
private:
	void update(Zombie* zombie, float delta);
public:
    ZombieFollowRunner();
	void update(float delta) override;

};
