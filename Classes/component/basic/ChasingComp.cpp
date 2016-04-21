#include "ChasingComp.h"
#include "component/pooled/KineticComp.h"
#include "component/pooled/DomainComp.h"
ChasingComp::ChasingComp() {
    
}

bool ChasingComp::chase(Entity* self, Entity* target) {
	//get kineticComp of both self and target. Without either of them, exit the function
	KineticComp* selfKin = (KineticComp*)self->components[COMP_CA::KINETIC_COMP];
	KineticComp* targetKin = (KineticComp*)target->components[COMP_CA::KINETIC_COMP];
	DomainComp* domain = (DomainComp*)target->components[COMP_CA::DOMAIN_COMP];
	if (NULL == selfKin || NULL == targetKin) return false;

	//add the relative distance to self's speed then clamp speed to max speed.
	Vec2 dis(targetKin->pos);
	dis.subtract(selfKin->pos);
	//if reach destination, return true and dont modify the current speed
	if (dis.length() < EPSILON || (domain && dis.length() <= domain->radius)) {
		return true;
	}
	//if haven't reach, modify the speed.
	selfKin->vel.add(dis);
	if (selfKin->vel.getLength() > selfKin->maxSpeed && selfKin->maxSpeed>0) {
		selfKin->vel.normalize();
		selfKin->vel.scale(selfKin->maxSpeed);
	}
	return false;
}