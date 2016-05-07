#include "RangeAttackRunner.h"
#include "world/World.h"
#include "component/pooled/ActionFlagComp.h"
#include "component/basic/RangeAttackComp.h"
#include "component/pooled/CombatComp.h"
#include "component/pooled/KineticComp.h"
#include "component/pooled/DomainComp.h"
#include "component/pooled/AnimComp.h"
#include "component/pooled/TrajectComp.h"
#include "util/AnimNameHelper.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "util/AudioDir.h"

#include "util/EntityFactory.h"

RangeAttackRunner::RangeAttackRunner() {
    
}

void RangeAttackRunner::update(float delta) {
	auto world = GET_WORLD;
	//We know that only zombie can shoot bullet. If we change this later, we just need to add other iterators.
	auto zombieIt = world->zombieList.begin();
	while (zombieIt != world->zombieList.end()) {
		updateEntity(*zombieIt, delta);
		zombieIt++;
	}
}

void RangeAttackRunner::updateEntity(Zombie* entity, float delta) {
	//get all the component
	//CCLOG("checking if this zombie can shoot bullet");
	if (!entity) return;
	auto rangeComp =(RangeAttackComp*)entity->components[COMP_CA::RANGE_ATTACK_COMP];
	auto combatComp = (CombatComp*)entity->components[COMP_CA::COMBAT_COMP];
	auto kineticComp = (KineticComp*)entity->components[COMP_CA::KINETIC_COMP];
	auto actionFlag = (ActionFlagComp*)entity->components[COMP_CA::ACTION_FLAG_COMP];
	auto domainComp = (DomainComp*)entity->components[COMP_CA::DOMAIN_COMP];
	if (entity->alliance == 0 || entity->marked) return;
	
	if (combatComp && combatComp->alliance == 0) return;
	//CCLOG("has positive alliance");
	if (rangeComp && combatComp && kineticComp && actionFlag && domainComp
		//if all the components are present
		&& actionFlag->isReady //ready to attack
		) {
		//find a closest player.
		//range attack will aim at player instead of zombies.
		//CCLOG("have all the comps and is ready");
		float oppDis = LARGE_NUM;
		Player* opponent = nullptr;
		auto playerIt = GET_WORLD->playerList.begin();
		while (playerIt != GET_WORLD->playerList.end()) {
			auto oppPlayer = (Player*)(*playerIt);
			if (oppPlayer) {
				//get oppPlayer components
				auto oppKin = (KineticComp*)oppPlayer->components[COMP_CA::KINETIC_COMP];
				
				auto oppHordeStatus = (HordeStatusComp*)oppPlayer->components[COMP_CA::HORDE_STATUS_COMP];
				//CCLOG("opp alliance is %d, my alliance is %d, domainComp-radius is %f, oppHorde has %d", oppPlayer->alliance, entity->alliance, domainComp->radius, oppHordeStatus->total);
				if (oppPlayer->alliance > 0 && oppPlayer->alliance != entity->alliance //opponent is in different alliance (enemy, not yourself)
					&& oppKin && oppHordeStatus //has all the required component
					&& !oppPlayer->marked //is not marked for death
					&& oppHordeStatus->total > 0 //has some zombie, otherwise it's no point to attack
					&& domainComp->contains(kineticComp->pos, oppKin->pos)//within the attack range
					&& oppKin->pos.distance(kineticComp->pos)<oppDis
					) {
					//CCLOG("found an opponent in loop");
					//save this opponent
					oppDis = oppKin->pos.distance(kineticComp->pos);
					opponent = oppPlayer;
				}
			}
			playerIt++;
		}
		//finally, check for if the opponent is found
		if (opponent) {
			//attack opponent
			//CCLOG("find one oppoennt");
			
			
			auto oppKin = (KineticComp*)opponent->components[COMP_CA::KINETIC_COMP];
			
			auto bullet=EntityFactory::createBullet(entity, oppKin->pos);
			auto traject=(TrajectComp*)bullet->components[COMP_CA::TRAJECT_COMP];
			traject->launch(kineticComp->pos, oppKin->pos);
			actionFlag->schedule();//reschedule for next bullet.

			//chucker playing attack animation
			auto animComp = (AnimComp*)entity->components[COMP_CA::ANIM_COMP];
			if (animComp) {
				animComp->forcePlay(entity, anim_name::directionalString("ATTACK", oppKin->pos - kineticComp->pos), 1);
			}
		}
		
	}

}