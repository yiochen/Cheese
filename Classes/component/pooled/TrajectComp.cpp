#include "TrajectComp.h"
#include "cocos2d.h"

#include "component/pooled/KineticComp.h"
#include "component/pooled/AnimComp.h"

USING_NS_CC;
TrajectComp::TrajectComp() {
    
}

void TrajectComp::init() {
	this->target.setZero();
	this->origin.setZero();
	this->curPos.setZero();
	this->arrived = true;
	this->speed = 100;
}
float cross(Vec2& v1, Vec2& v2) {
	CCLOG("v1 is %f, %f, v2 is %f, %f", v1.x, v1.y, v2.x, v2.y);
	return v1.x*v2.y - v1.y*v2.x;
}
void TrajectComp::update(Entity* entity, float delta) {
	KineticComp* kin = (KineticComp*)entity->components[COMP_CA::KINETIC_COMP];
	

	if (Vec2(this->target - this->curPos).dot(Vec2(this->target - this->origin)) <=0.0f) {
		/*CCLOG("target is %f, %f, curpos is %f, %f, origin is %f,%f and the cross is %f, fu", target.x, target.y, curPos.x, curPos.y, origin.x, origin.y, cross(curDis,oriDis));*/
		//Vec2(this->target - this->curPos).cross(Vec2(this->target - this->origin))
		this->arrived = true; CCLOG("arrived");
		//forceplaying explosion anymation
		AnimComp* anim = (AnimComp*)entity->components[COMP_CA::ANIM_COMP];
		if (anim) {
			anim->forcePlay(entity, "EXPLODE",1, true);
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
void TrajectComp::launch(Vec2 origin, Vec2 target) {
	this->target.set(target);
	this->origin.set(origin);
	this->curPos.set(origin);
	this->arrived = false;
	CCLOG("launched");
}