#include "FollowingComp.h"
#include "component/pooled/KineticComp.h"

FollowingComp::FollowingComp() {
    
}

void FollowingComp::follow(Entity* self, Entity* target, float delta) {
	KineticComp* selfKin = (KineticComp*)self->components[COMP_CA::KINETIC_COMP];
	KineticComp* targetKin = (KineticComp*)target->components[COMP_CA::KINETIC_COMP];
	if (selfKin && targetKin) {
		Vec2 change(targetKin->vel);
		change.scale(delta);
		selfKin->vel.add(change);
		if (selfKin->vel.getLength() > selfKin->maxSpeed) {
			selfKin->vel.normalize();
			selfKin->vel.scale(selfKin->maxSpeed);
		}
	}
}
