#include "StatRunner.h"
#include "entity/zombie/Zombie.h"
#include "world/World.h"
#include "component/pooled/CombatComp.h"
#include "component/pooled/AnimComp.h"
#include "component/pooled/KineticComp.h"
#include "util/AnimNameHelper.h"
#include "cocos2d.h"
USING_NS_CC;
StatRunner::StatRunner() {
    
}
void StatRunner::update(float delta) {
	//iterate over zombie
	World* world = World::instance();
	auto zombieIt = world->zombieList.begin();
	while (zombieIt != world->zombieList.end()) {
		updateEntity(*zombieIt, delta);
		zombieIt++;
	}
}
void StatRunner::updateEntity(Entity* entity, float delta) {
	CombatComp* combatComp = (CombatComp*)entity->components[COMP_CA::COMBAT_COMP];
	if (combatComp) {
		combatComp->hp -= combatComp->pendingDmg;
		//CCLOG("zombie took %d damage, now hp is %d", combatComp->pendingDmg, combatComp->hp);
		combatComp->pendingDmg = 0;
		if (!combatComp->isDying && combatComp->hp <= 0) {
			//the entity is dying.
			combatComp->isDying = true;
			//play dying anymation
			CCLOG("a zombie is dying, playing the dying animation");
			AnimComp* anim = (AnimComp*)entity->components[COMP_CA::ANIM_COMP];
			KineticComp* kin = (KineticComp*)entity->components[COMP_CA::KINETIC_COMP];
			if (anim && kin) {
				anim->forcePlay(entity, anim_name::directionalString("DEATH", kin->vel), 1, true);
			}
			combatComp->isDead = false;
		}
	}
}