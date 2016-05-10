#pragma once
#include "EntityRunner.h"
#include "entity/Entity.h"
#include "entity/zombie/Zombie.h"
#include "world/World.h"
/*This is for player(swiss) to run away when all his zombie dies*/
class EscapeRunner : public EntityRunner {
public:
	EscapeRunner();
	void update(float delta) override;
	void updateEntity(Player* entity, float delta);
};
