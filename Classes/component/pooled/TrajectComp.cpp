#include "TrajectComp.h"
#include "cocos2d.h"

#include "component/pooled/KineticComp.h"

USING_NS_CC;
TrajectComp::TrajectComp() {
    
}

void TrajectComp::init() {
	this->target.setZero();
	this->origin.setZero();
	this->curPos.setZero();
}

void TrajectComp::update(Entity* entity) {
	KineticComp* kin = (KineticComp*)entity->components[COMP_CA::KINETIC_COMP];
	if (kin) {
		kin->pos.set(this->curPos);
		kin->vel.setZero();
	}

}
void TrajectComp::launch(Vec2 origin, Vec2 target) {
	this->target.set(target);
	this->origin.set(origin);
	this->curPos.set(origin);
	
}