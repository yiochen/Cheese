#include "ZombieFollowRunner.h"
#include "world/World.h"

#include "component/pooled/KineticComp.h"
#include "component/basic/ChasingComp.h"
#include "component/basic/SeperationComp.h"
#include "component/basic/FollowingComp.h"
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
		
		//apply friction to reduce the effect of the previous frame;
		//KineticComp* kinetic = (KineticComp*)zombie->components[COMP_CA::KINETIC_COMP];
		//kinetic->vel.scale(0.99f);

		ChasingComp* chasingComp = (ChasingComp*)zombie->components[COMP_CA::CHASING_COMP];
		if (chasingComp) {
			chasingComp->chase(zombie, player, delta);
		}
		SeperationComp* seperationComp = (SeperationComp*)zombie->components[COMP_CA::SEPERATION_COMP];
		HordeStatusComp* hordeStatus = (HordeStatusComp*)player->components[COMP_CA::HORDE_STATUS_COMP];
		if (seperationComp && hordeStatus) {
			
			//seperate from the average point
			//if the target is really close to the entity's position. Just choose a random direction for speration. 
			Vec2 center(hordeStatus->sumPos);
			center.scale(1.0f / (float)(hordeStatus->total));
			seperationComp->seperate(zombie, center, delta);
		}
		
		FollowingComp* followingComp = (FollowingComp*)zombie->components[COMP_CA::FOLLOWING_COMP];
		if (followingComp) {
			followingComp->follow(zombie, player, delta);
		}

		
	}
}