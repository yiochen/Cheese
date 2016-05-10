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
	pointsRemaining = 0;
}

void HordeStatusComp::zeroPos() {
	this->sumPos.setZero();
}

//incorporate stats from horde into a stray zombie, call when recruits a stray zombie
void HordeStatusComp::updateStray(Entity* e) {
	CombatComp* combatComp = (CombatComp*)(e->components[COMP_CA::COMBAT_COMP]);
	ActionFlagComp* actionFlagComp = (ActionFlagComp*)(e->components[COMP_CA::ACTION_FLAG_COMP]);
	DomainComp* domainComp = (DomainComp*)(e->components[COMP_CA::DOMAIN_COMP]);
	if (((Zombie*)e)->player && actionFlagComp && domainComp && combatComp) {

		HordeStatusComp* hordeStatusComp = (HordeStatusComp*)(((Zombie*)e)->player->components[COMP_CA::HORDE_STATUS_COMP]);
		if (((Zombie*)e)->catagory == ZOMBIE_CA::STINKIE) {
			actionFlagComp->interval = hordeStatusComp->zombieStat[ZOMBIE_STAT_CA::STINKIE_ATTACKSPEED];
			combatComp->damage = (int)hordeStatusComp->zombieStat[ZOMBIE_STAT_CA::STINKIE_ATTACK];
			
			CCLOG("The hp of hordestatus is now %d (WHEN RECRUIT) ", (int)hordeStatusComp->zombieStat[ZOMBIE_STAT_CA::STINKIE_HP]);
			combatComp->setHP((int)hordeStatusComp->zombieStat[ZOMBIE_STAT_CA::STINKIE_HP]);
			CCLOG("The hp of this zombie is now %d ", combatComp->hp);
		}
		if (((Zombie*)e)->catagory == ZOMBIE_CA::CHUCKER) {
			actionFlagComp->interval = hordeStatusComp->zombieStat[ZOMBIE_STAT_CA::CHUCKER_ATTACKSPEED];
			combatComp->damage = (int)hordeStatusComp->zombieStat[ZOMBIE_STAT_CA::CHUCKER_ATTACK];
			combatComp->hp = (int)hordeStatusComp->zombieStat[ZOMBIE_STAT_CA::CHUCKER_HP];
			domainComp->radius = (int)hordeStatusComp->zombieStat[ZOMBIE_STAT_CA::CHUCKER_RANGE];
		}
		if (((Zombie*)e)->catagory == ZOMBIE_CA::HOLY_BONE) {
			actionFlagComp->interval = hordeStatusComp->zombieStat[ZOMBIE_STAT_CA::HOLY_BONE_ATTACK_SPEED];
			combatComp->damage = (int)hordeStatusComp->zombieStat[ZOMBIE_STAT_CA::HOLY_BONE_HEAL];
			combatComp->hp = (int)hordeStatusComp->zombieStat[ZOMBIE_STAT_CA::HOLY_BONE_HP];
			domainComp->radius = (int)hordeStatusComp->zombieStat[ZOMBIE_STAT_CA::HOLY_BONE_RANGE];

		}
		else{
			CCLOG("the category # of this zombie is %d", ((Zombie*)e)->catagory);
		}
	}
}
void HordeStatusComp::updateHorde() {
	World* world = World::instance();
	auto zombieIt = world->zombieList.begin();
	auto playerIt = world->playerList.begin();
	while (zombieIt != world->zombieList.end()) {
		//TODO:: no need to update the stats every frame. Make a function that can be called when army tab closes (or gameScene resumes)
		// this is not called every frame, only called when an upgrade is allied or a zombie is recruited
		
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
//TODO: this is temporary, if the structure of zombieStat changes, this could be removed.
int HordeStatusComp::getMaxHP(ZOMBIE_CA type) {

	switch (type) {
	case ZOMBIE_CA::CHUCKER:
		return zombieStat[ZOMBIE_STAT_CA::CHUCKER_HP];
	case ZOMBIE_CA::STINKIE:
		return zombieStat[ZOMBIE_STAT_CA::STINKIE_HP];
	case ZOMBIE_CA::HOLY_BONE:
		return zombieStat[ZOMBIE_STAT_CA::HOLY_BONE_HP];
	}
	return 0;
}