#include "ZombieFollowRunner.h"
#include "world/World.h"

#include "component/basic/ChasingComp.h"

ZombieFollowRunner::ZombieFollowRunner() {
    
}

void ZombieFollowRunner::update(float delta) {
	//iterate through zombielist
	World* world = World::instance();
	auto zombieIt = world->zombieList.begin();
	while (zombieIt != world->zombieList.end()) {
		update((Zombie*)*zombieIt, delta);
		zombieIt++;
	}
}

void ZombieFollowRunner::update(Zombie* zombie, float delta) {
	Player* player = zombie->player;
	
	if (NULL == player) {
		//strayed zombie. doesnt have a player to follow

	}
	else {
		//has a player to follow
		//zombie chasing player is out of domain
		ChasingComp* chasingComp = (ChasingComp*)zombie->components[COMP_CA::CHASING_COMP];
		if (chasingComp) {
			chasingComp->chase(zombie, zombie->player);
		}
	}
}