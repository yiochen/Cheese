#pragma once
#include "entity/Entity.h"
#include "runner/EntityRunner.h"
#include "entity/zombie/Zombie.h"
#include "entity/player/Player.h"

/*Tally the player's zombie on each frame and update the position in player's HordeStatusComp
	This runner also update the zombieSensorComp(not done yet)
*/
class ZombieTallyRunner:public EntityRunner {
private:
	void countZombie(Zombie* zombie);
public:
    ZombieTallyRunner();
	void update(float delta) override;

};
