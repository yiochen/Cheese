#include "CheatSystem.h"
#include "util/EntityFactory.h"
#include "component/pooled/TrajectComp.h"

void cheat_system::killOneZombie() {
	CCLOG("pressed C");
	World* world = World::instance();
	auto zombieIt = world->zombieList.begin();
	while (zombieIt != world->zombieList.end()) {
		Zombie* zombie=(Zombie*)(*zombieIt);
		if (zombie) {
			auto combatComp = (CombatComp*)zombie->components[COMP_CA::COMBAT_COMP];
			if (combatComp) {
				combatComp->hp = -10;
				CCLOG("Kill a zombie");
				combatComp->isDead = false;
				combatComp->isDying = false;
				break;
			}
		}
		zombieIt++;
	}
}

void cheat_system::launchBullet() {
	CCLOG("creating bullet");
	World* world = World::instance();
	Player* player = world->swiss;
	if (player) {
		//create a bullet
		//create a bullet aiming at 10,10
		auto bullet = EntityFactory::createBullet(player, Vec2(100, 100));
		CCLOG("launching bullet");
		TrajectComp* traject = (TrajectComp*)bullet->components[COMP_CA::TRAJECT_COMP];
		traject->launch(player, traject->target);
	}
}