#pragma once
#include"world/world_include.h"
#include "world/World.h"

/*this class contain some helper static methods for creating entities in the game. 
Note that the entity created is not added to to world or renderlist yet.*/
namespace EntityFactory {

	
	Zombie* createZombie(Player* player) {
		World* world = World::instance();
		auto zombiePool = world->getZombiePool();
		Zombie* zombie = zombiePool->New();
		zombie->init();
		zombie->player = player;
		HordeStatusComp* hordeStatus = (HordeStatusComp*)player->components[COMP_CA::HORDE_STATUS_COMP];
		hordeStatus->total++;
		//kinetic Component
		KineticComp* kineticComp = world->getCompPool<KineticComp>(COMP_CA::KINETIC_COMP)->New();
		zombie->components[COMP_CA::KINETIC_COMP] = kineticComp;
		kineticComp->maxSpeed = 100.0f + RandomHelper::random_real<float>(-20.0f, 20.0f);
		//TODO kinetic position should be relative to the world;
		kineticComp->pos.set(100, 100);
		kineticComp->vel.set(0, 0);
		//animation Component
		AnimComp* animComp = world->getCompPool<AnimComp>(COMP_CA::ANIM_COMP)->New();
		//following is to be read from a file
		
		animComp->name = "basic_zombie";
		zombie->catagory = ZOMBIE_CA::STINKIE;
		hordeStatus->zombieCounts[ZOMBIE_CA::STINKIE]++;
		/*}
		else {
			animComp->name = "chucker";
			zombie->catagory = ZOMBIE_CA::CHUCKER;
			hordeStatus->zombieCounts[ZOMBIE_CA::CHUCKER]++;
		}*/

		animComp->newAnimState = A_WALK_FORTH;
		zombie->components[COMP_CA::ANIM_COMP] = animComp;
		//add chasingComp
		zombie->components[COMP_CA::CHASING_COMP] = world->commonComps[COMP_CA::CHASING_COMP];
		zombie->components[COMP_CA::SEPERATION_COMP] = world->commonComps[COMP_CA::SEPERATION_COMP];
		zombie->components[COMP_CA::FOLLOWING_COMP] = world->commonComps[COMP_CA::FOLLOWING_COMP];
		return zombie;
	}
	Player * createPlayer(bool isHuman) {
		World* world = World::instance();
		auto pool = world->getPlayerPool();
		auto player=pool->New();

		//read lua here

		player->init();
		//keyboard Component
		if (isHuman) {
			player->components[COMP_CA::KEYBOARD_COMP] = world->commonComps[COMP_CA::KEYBOARD_COMP];
		}
		
		//kinetic Component
		KineticComp* kineticComp = world->getCompPool<KineticComp>(COMP_CA::KINETIC_COMP)->New();
		player->components[COMP_CA::KINETIC_COMP] = kineticComp;
		kineticComp->maxSpeed = 100.0f;
		//TODO kinetic position should be relative to the world;
		kineticComp->pos.set(0, 0);
		kineticComp->vel.set(0, 0);
		//animation Component
		AnimComp* animComp = world->getCompPool<AnimComp>(COMP_CA::ANIM_COMP)->New();
		//following is to be read from a file
		animComp->name = "swiss";
		animComp->newAnimState = A_WALK_FORTH;
		player->components[COMP_CA::ANIM_COMP] = animComp;
		DomainComp* domainComp = world->getCompPool<DomainComp>(COMP_CA::DOMAIN_COMP)->New();
		player->components[COMP_CA::DOMAIN_COMP] = domainComp;
		domainComp->radius = 50;//set the radius of domain to 50 for now. TODO: to be changed to read from lua
		HordeStatusComp* hordeStatus = world->getCompPool<HordeStatusComp>(COMP_CA::HORDE_STATUS_COMP)->New();
		hordeStatus->init();
		player->components[COMP_CA::HORDE_STATUS_COMP] = hordeStatus;
		
		return player;
	}
}
