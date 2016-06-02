#include "ZombieFollowRunner.h"
#include "world/World.h"

#include "component/pooled/KineticComp.h"
#include "component/basic/ChasingComp.h"
#include "component/basic/SeparationComp.h"
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
		SeparationComp* separationComp = (SeparationComp*)zombie->components[COMP_CA::SEPARATION_COMP];
		HordeStatusComp* hordeStatus = (HordeStatusComp*)player->components[COMP_CA::HORDE_STATUS_COMP];
		if (separationComp && hordeStatus) {
			
			//separate from the average point
			//if the target is really close to the entity's position. Just choose a random direction for speration. 
			Vec2 center(hordeStatus->sumPos);
			
			if (hordeStatus->total > 1) {
				//do separation only when the population is greater than 1
				center.scale(1.0f / (float)(hordeStatus->total));
				separationComp->separate(zombie, center, delta);
			}
			
		}
		
		FollowingComp* followingComp = (FollowingComp*)zombie->components[COMP_CA::FOLLOWING_COMP];
		if (followingComp) {
			followingComp->follow(zombie, player, delta);
		}

		
	}
}