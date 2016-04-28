#include "CheatSystem.h"

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