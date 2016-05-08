#include "HealRunner.h"
#include "world/World.h"
#include "component/pooled/ActionFlagComp.h"
#include "component/pooled/CombatComp.h"
#include "component/basic/HealComp.h"
#include "component/pooled/HordeStatusComp.h"
#include "component/pooled/AnimComp.h"
#include "component/pooled/DomainComp.h"
#include "component/pooled/CombatComp.h"
#include "component/pooled/KineticComp.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "util/AudioDir.h"

#include "entity/attachment/Attachment.h"
#include "util/AttachmentFactory.h"
#include "util/AnimNameHelper.h"

HealRunner::HealRunner() {
    
}

void HealRunner::update(float delta) {
	auto world = GET_WORLD;

	auto zombieIt = world->zombieList.begin();
	while (zombieIt != world->zombieList.end()) {
		updateEntity(*zombieIt, delta);
		zombieIt++;
	}
}

void HealRunner::updateEntity(Zombie* zombie, float delta) {
	if (!zombie) {
		CCLOG("ERROR::zombie is null in healRunner");
	}
	HordeStatusComp *hordeStatus = nullptr;
	if (zombie->player) {
		hordeStatus = (HordeStatusComp*)zombie->player->components[COMP_CA::HORDE_STATUS_COMP];
	}
	else {
		//if the zombie doesn't have a player. it is a stray zombie. quit right away 
		return;
	}
	World* world = GET_WORLD;
	auto heal = (HealComp*)zombie->components[COMP_CA::HEAL_COMP];
	auto domain = (DomainComp*)zombie->components[COMP_CA::DOMAIN_COMP];
	auto actionFlag = (ActionFlagComp*)zombie->components[COMP_CA::ACTION_FLAG_COMP];
	auto anim = (AnimComp*)zombie->components[COMP_CA::ANIM_COMP];
	auto combat = (CombatComp*)zombie->components[COMP_CA::COMBAT_COMP];
	auto kin = (KineticComp*)zombie->components[COMP_CA::KINETIC_COMP];
	if (heal && domain && actionFlag && anim && domain && combat && hordeStatus //have all the components
		&& actionFlag->isReady //the zombie can heal
		) {
		CCLOG("healer start looking for patients");
		//look for any zombie touching the domain;
		auto zombieIt = world->zombieList.begin();
		int patientCount = 0;
		while (zombieIt != world->zombieList.end()) {
			Zombie* targetZom = (Zombie*)(*zombieIt);
			if (targetZom) {
				KineticComp* targetKin = (KineticComp*)targetZom->components[COMP_CA::KINETIC_COMP];
				CombatComp* targetComp = (CombatComp*)targetZom->components[COMP_CA::COMBAT_COMP];
				if (targetZom->alliance == zombie->alliance && //same alliance
					domain->contains(kin->pos, targetKin->pos) //the zombie is within the range
					//TODO if the zombie doesn't need heal, dont heal it
					) {
					//heal the zombie
					AttachmentFactory::createHealAtt(targetZom);
					targetComp->hp += combat->damage;
					//TODO::check max hp from hordestatus
					patientCount++;
				}
			}
			zombieIt++;
		}
		if (patientCount > 0) {
			anim->forcePlay(zombie,
				anim_name::directionalString("ATTACK", kin->vel),
				1);
			actionFlag->schedule();
		}
	}
}