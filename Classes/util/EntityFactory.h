#pragma once
#include"world/world_include.h"
#include "world/World.h"
#include "device/LuaDevice.h"
#include "luacppinterface.h"

/*this class contain some helper static methods for creating entities in the game. 
Note that the entity created is not added to to world or renderlist yet.*/
namespace EntityFactory {

	void initEntity(Entity* entity, LuaTable& luaTable);
	Zombie* createZombie(Player* player,LuaFunction<LuaTable()>& luaFunc);
	Zombie* createStrayZombie(ZOMBIE_CA);
	Player* createPlayer(bool isHuman);

	/*
	//TODO: createZombie and createPlayer should be combined when the lua function is ready
	Zombie* createZombie(Player* player) {
		LuaDevice* lua = LuaDevice::instance();


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
		kineticComp->pos.set(((KineticComp*)player->components[COMP_CA::KINETIC_COMP])->pos);
		//kineticComp->pos.set(100, 100);
		kineticComp->vel.set(0, 0);
		//animation Component
		AnimComp* animComp = world->getCompPool<AnimComp>(COMP_CA::ANIM_COMP)->New();
		//following is to be read from a file
		
		switch (RandomHelper::random_int(0, 2)) {
		case 0:
			animComp->name = "basic_zombie";
			break;
		case 1:
			animComp->name = "chucker";
			break;
		case 2:
			animComp->name = "healer";
			break;
		}
		
		zombie->catagory = ZOMBIE_CA::STINKIE;
		hordeStatus->zombieCounts[ZOMBIE_CA::STINKIE]++;
		

		animComp->newAnimState = A_WALK_FORTH;
		zombie->components[COMP_CA::ANIM_COMP] = animComp;
		//add chasingComp
		zombie->components[COMP_CA::CHASING_COMP] = world->commonComps[COMP_CA::CHASING_COMP];
		zombie->components[COMP_CA::SEPERATION_COMP] = world->commonComps[COMP_CA::SEPERATION_COMP];
		zombie->components[COMP_CA::FOLLOWING_COMP] = world->commonComps[COMP_CA::FOLLOWING_COMP];
		zombie->components[COMP_CA::MELEE_ATTACK_COMP] = world->commonComps[COMP_CA::MELEE_ATTACK_COMP];
		CombatComp* combatComp = world->getCompPool<CombatComp>(COMP_CA::COMBAT_COMP)->New();
		combatComp->init();
		combatComp->setHP(100);
		combatComp->setDamage(50);
		//Don't do the following way. right now it is just testing
		if (player == world->swiss) {//should not compare with swiss. Should be two seperated function for AI player and human player.
			combatComp->alliance = 1;
		}
		else {
			combatComp->alliance = 2;
		}
		zombie->components[COMP_CA::COMBAT_COMP] = combatComp;
		DomainComp* domainComp = world->getCompPool<DomainComp>(COMP_CA::DOMAIN_COMP)->New();
		domainComp->init();
		domainComp->radius = 50.0f;
		zombie->components[COMP_CA::DOMAIN_COMP] = domainComp;
		ActionFlagComp* actionComp = world->getCompPool<ActionFlagComp>(COMP_CA::ACTION_FLAG_COMP)->New();
		actionComp->init();
		//testing actionComp
		actionComp->interval = 3.0f;//3 second
		zombie->components[COMP_CA::ACTION_FLAG_COMP] = actionComp;

		return zombie;
	}
	Player * createPlayer(bool isHuman) {
		World* world = World::instance();
		auto pool = world->getPlayerPool();
		auto player=pool->New();

		//read lua here

		player->init();
		//keyboard Component
	
		
		//kinetic Component
		KineticComp* kineticComp = world->getCompPool<KineticComp>(COMP_CA::KINETIC_COMP)->New();
		player->components[COMP_CA::KINETIC_COMP] = kineticComp;
		kineticComp->maxSpeed = 100.0f;
		//TODO kinetic position should be relative to the world;
		if (isHuman) {
			player->components[COMP_CA::KEYBOARD_COMP] = world->commonComps[COMP_CA::KEYBOARD_COMP];
			kineticComp->pos.set(500, 100);
			kineticComp->vel.set(0, 0);
		}

		if (!isHuman) {
			kineticComp->pos.set(500, 500);

		}

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
	*/
}
