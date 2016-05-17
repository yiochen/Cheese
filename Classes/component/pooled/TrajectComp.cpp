#include "TrajectComp.h"
#include "cocos2d.h"
#include "world/World.h"
#include "component/pooled/KineticComp.h"
#include "component/pooled/AnimComp.h"

#include "component/pooled/DomainComp.h"
#include "component/pooled/CombatComp.h"
USING_NS_CC;
TrajectComp::TrajectComp() {
    
}

void TrajectComp::init() {
	this->target.setZero();
	this->origin.setZero();
	this->curPos.setZero();
	this->arrived = true;
	this->speed = 100;
	this->damage = 0;
}
float cross(Vec2& v1, Vec2& v2) {
	CCLOG("v1 is %f, %f, v2 is %f, %f", v1.x, v1.y, v2.x, v2.y);
	return v1.x*v2.y - v1.y*v2.x;
}
void TrajectComp::update(Entity* entity, float delta) {
	KineticComp* kin = (KineticComp*)entity->components[COMP_CA::KINETIC_COMP];
	

	if (!arrived && Vec2(this->target - this->curPos).dot(Vec2(this->target - this->origin)) <=0.0f) {
		/*CCLOG("target is %f, %f, curpos is %f, %f, origin is %f,%f and the cross is %f, fu", target.x, target.y, curPos.x, curPos.y, origin.x, origin.y, cross(curDis,oriDis));*/
		//Vec2(this->target - this->curPos).cross(Vec2(this->target - this->origin))
		this->arrived = true;
		//forceplaying explosion anymation
		AnimComp* anim = (AnimComp*)entity->components[COMP_CA::ANIM_COMP];
		DomainComp* domain = (DomainComp*)entity->components[COMP_CA::DOMAIN_COMP];

		if (anim) {
			anim->forcePlay(entity, A_SPIT_HIT,1, true);
		}
		//below is not good code, because it will make trajet component only suitable for bullets.
		//but for simplicity, I will do that TODO:: change it
		//iterate over all the zombies, find zombies that are withing range
		auto zombieIt = GET_WORLD->zombieList.begin();
		while (zombieIt != GET_WORLD->zombieList.end()) {
			Zombie* zombie = (Zombie*)(*zombieIt);
			if (zombie && zombie->alliance>0 && zombie->alliance!=entity->alliance) {
				auto victimKin = (KineticComp*)zombie->components[COMP_CA::KINETIC_COMP];
				auto victimComb = (CombatComp*)zombie->components[COMP_CA::COMBAT_COMP];
				if (victimKin && victimComb && domain && domain->contains(kin->pos,victimKin->pos)) {
					victimComb->pendingDmg += this->damage;
				}
			}
			zombieIt++;
		}

	}
	if (kin && !arrived) {
		Vec2 dis(this->target - this->origin);
		dis.normalize();
		dis.scale(this->speed*delta);
		this->curPos.add(dis);
		kin->pos.set(this->curPos);
		kin->vel.setZero();
	}
}
void TrajectComp::launch(Entity* launcher, Vec2 target) {
	if (!launcher) {
		CCLOG("ERROR:: launcher null in trajectComp");
		return;
	}
	KineticComp* kin = (KineticComp*)launcher->components[COMP_CA::KINETIC_COMP];
	CombatComp* comb = (CombatComp*)launcher->components[COMP_CA::COMBAT_COMP];

	if (!kin) {
		CCLOG("ERROR:: launcher doesnt have kinetic Comp in trajectcomp");
		return;
	}
	if (!comb) {
		this->damage = 100; //this is for cheat, if the player shoots a bullet(L key). cost 100 damage
	}
	else {
		this->damage = comb->damage;
	}
	this->target.set(target);
	this->origin.set(kin->pos);
	this->curPos.set(kin->pos);
	
	this->arrived = false;
	CCLOG("launched with damage %d", comb->damage);
}