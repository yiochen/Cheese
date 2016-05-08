#include "HordeStatusComp.h"
#include "DomainComp.h"
#include "ActionFlagComp.h"
#include "CombatComp.h"
#include "world/World.h"

HordeStatusComp::HordeStatusComp() {
    
}

void HordeStatusComp::init() {
	this->sumPos.setZero();
	this->total = 0;
	for (int i = ZOMBIE_CA::ZOMBIE_START; i < ZOMBIE_CA::ZOMBIE_END; i++) {
		this->zombieCounts[(ZOMBIE_CA)i] = 0;
	}
	pointsRemaining = 40;
}

void HordeStatusComp::zeroPos() {
	this->sumPos.setZero();
}

void HordeStatusComp::updateHorde() {
	World* world = World::instance();
	auto zombieIt = world->zombieList.begin();
	auto playerIt = world->playerList.begin();
	while (zombieIt != world->zombieList.end()) {

		Zombie* z = ((Zombie*)*zombieIt);
		CombatComp* combatComp = (CombatComp*)(z->components[COMP_CA::COMBAT_COMP]);
		ActionFlagComp* actionFlagComp = (ActionFlagComp*)(z->components[COMP_CA::ACTION_FLAG_COMP]);
		DomainComp* domainComp = (DomainComp*)(z->components[COMP_CA::DOMAIN_COMP]);
		if (((Zombie*)*zombieIt)->player && actionFlagComp && domainComp && combatComp) {

			HordeStatusComp* hordeStatusComp = (HordeStatusComp*)(z->player->components[COMP_CA::HORDE_STATUS_COMP]);
			if (z->catagory == ZOMBIE_CA::STINKIE) {
				actionFlagComp->interval= hordeStatusComp->zombieStat[ZOMBIE_STAT_CA::STINKIE_ATTACKSPEED];
				combatComp->damage = (int)hordeStatusComp->zombieStat[ZOMBIE_STAT_CA::STINKIE_ATTACK];
			}
			if (z->catagory == ZOMBIE_CA::CHUCKER) {
				actionFlagComp->interval = hordeStatusComp->zombieStat[ZOMBIE_STAT_CA::CHUCKER_ATTACKSPEED];
				combatComp->damage = (int)hordeStatusComp->zombieStat[ZOMBIE_STAT_CA::CHUCKER_ATTACK];
				domainComp->radius = (int)hordeStatusComp->zombieStat[ZOMBIE_STAT_CA::CHUCKER_RANGE];
			}
			if (z->catagory == ZOMBIE_CA::HOLY_BONE) {
				actionFlagComp->interval = hordeStatusComp->zombieStat[ZOMBIE_STAT_CA::HOLY_BONE_ATTACK_SPEED];
				combatComp->damage = (int)hordeStatusComp->zombieStat[ZOMBIE_STAT_CA::HOLY_BONE_HEAL];
				domainComp->radius = (int)hordeStatusComp->zombieStat[ZOMBIE_STAT_CA::HOLY_BONE_RANGE];

			}
		}


		zombieIt++;
	}
}