#include "ZombieFollowRunner.h"
#include "world/World.h"

#include "component/basic/ChasingComp.h"
#include "component/basic/SeperationComp.h"
#include "component/pooled/HordeStatusComp.h"

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
			chasingComp->chase(zombie, player, delta);
		}
		SeperationComp* seperationComp = (SeperationComp*)zombie->components[COMP_CA::SEPERATION_COMP];
		HordeStatusComp* hordeStatus = (HordeStatusComp*)player->components[COMP_CA::HORDE_STATUS_COMP];
		if (!seperationComp) CCLOG("no seperation comp");
		if (!hordeStatus) CCLOG("no horde status");
		if (seperationComp && hordeStatus) {
			
			//seperate from the average point
			//if the target is really close to the entity's position. Just choose a random direction for speration. 
			Vec2 center(hordeStatus->sumPos);
			center.scale(1.0f / (float)hordeStatus->total);
			CCLOG("center sum is  %f, %f, and total is %d", center.x, center.y, hordeStatus->total);
			seperationComp->seperate(zombie, center, delta);
		}
		
	}
}