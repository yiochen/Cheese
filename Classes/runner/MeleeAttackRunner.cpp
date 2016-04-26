#include "MeleeAttackRunner.h"
#include "world/World.h"
#include "component/pooled/ActionFlagComp.h"
#include "component/basic/MeleeAttackComp.h"
#include "component/pooled/CombatComp.h"
#include "component/pooled/KineticComp.h"
#include "component/pooled/DomainComp.h"

MeleeAttackRunner::MeleeAttackRunner() {
    
}

void MeleeAttackRunner::update(float delta) {
	//we assume that only zombie attacks for now.
	auto world = GET_WORLD;
	auto zombieIt = world->zombieList.begin();
	while (zombieIt != world->zombieList.end()) {
		updateEntity(*zombieIt, delta);
		zombieIt++;
	}
}
void MeleeAttackRunner::updateEntity(Entity* entity, float delta) {
	auto meleeComp = entity->components[COMP_CA::MELEE_ATTACK_COMP];
	if (!meleeComp) return;
	auto combatComp = (CombatComp*)entity->components[COMP_CA::COMBAT_COMP];
	auto kineticComp = (KineticComp*)entity->components[COMP_CA::KINETIC_COMP];
	auto actionFlag = (ActionFlagComp*)entity->components[COMP_CA::ACTION_FLAG_COMP];
	auto domainComp = (DomainComp*)entity->components[COMP_CA::DOMAIN_COMP];
	if (combatComp && kineticComp && actionFlag && domainComp //check if all the component exist
		&& actionFlag->isReady //ready to attack
		&& combatComp->damage>EPSILON //it has attack power (not healer)
		) {
		//finally start looking for opponents.
		int alliance = combatComp->alliance;
		//iterate through all the zombies
		auto zombieIt = GET_WORLD->zombieList.begin();
		Zombie* opponent = nullptr;
		float oppDis = 100000.0f; //supper big number.
		while (zombieIt != GET_WORLD->zombieList.end()) {
			//find the opponent zombie closes to it self.
			auto oppZombie = (Zombie*)(*zombieIt);
			auto oppCombat = (CombatComp*)oppZombie->components[COMP_CA::COMBAT_COMP];
			auto oppKinetic = (KineticComp*)oppZombie->components[COMP_CA::KINETIC_COMP];
			if (oppCombat && oppKinetic && oppCombat->alliance!=alliance) {
				if (opponent == nullptr) {
					opponent = oppZombie;
					oppDis = kineticComp->pos.getDistance(oppKinetic->pos);
				}
				else {
					float newDis = kineticComp->pos.getDistance(oppKinetic->pos);
					if (newDis < oppDis) {
						oppDis = newDis;
						opponent = oppZombie;
					}

				}
			}
			zombieIt++;
		}//while
		//found the opponent zombie, check if it's within the attack range
		if (domainComp->contains(kineticComp->pos, ((KineticComp*)(opponent->components[COMP_CA::KINETIC_COMP]))->pos)) {
			//can finally attack.
			//TODO:play animation once.

			//reset the timer for next attack
			((CombatComp*)opponent->components[COMP_CA::COMBAT_COMP])->pendingDmg += combatComp->damage;
			actionFlag->schedule();
			CCLOG("attack an enermy");
		}
	}
}