#include "ZombieTallyRunner.h"
#include "world/World.h"

#include "component/pooled/HordeStatusComp.h"
#include "component/pooled/KineticComp.h"
#include "component/pooled/ZombieSensorComp.h"

ZombieTallyRunner::ZombieTallyRunner() {
    
}

void ZombieTallyRunner::update(float delta) {
	//clear all player's horde status
	World*  world = World::instance();
	auto playerIt = world->playerList.begin();
	while (playerIt != world->playerList.end()) {
		HordeStatusComp* hordeStatus = (HordeStatusComp*)(*playerIt)->components[COMP_CA::HORDE_STATUS_COMP];
		if (NULL != hordeStatus) {
			//clear all the player's horde status.
			hordeStatus->zeroPos();
		}
		playerIt++;
	}
	//recalculating the horde status by iterating over all the zombies.
	auto zombieIt = world->zombieList.begin();
	while (zombieIt != world->zombieList.end()) {
		//get the player the zombie is following
		countZombie(*zombieIt);
		zombieIt++;
	}
}
void ZombieTallyRunner::countZombie(Zombie* zombie) {
	Player* player = zombie->player;
	if (player) {
		HordeStatusComp* hordeStatus = (HordeStatusComp*)player->components[COMP_CA::HORDE_STATUS_COMP];
		KineticComp* kinetic = (KineticComp*)zombie->components[COMP_CA::KINETIC_COMP];
		if (NULL == hordeStatus || NULL == kinetic) return;
		hordeStatus->sumPos.add(kinetic->pos);
	}
	//
	
}