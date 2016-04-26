#include "SeperationComp.h"
#include "component/pooled/KineticComp.h"
#include <cmath> 
SeperationComp::SeperationComp() {
    
}
void rotateTo(Vec2& vec, float angle) {
	float length = vec.getLength();
	vec.set(cos(angle), sin(angle));
	vec.scale(length);
}
void SeperationComp::seperate(Entity* entity, Vec2 target, float delta) {
	KineticComp* kinetic = (KineticComp*)entity->components[COMP_CA::KINETIC_COMP];
	if (kinetic) {
		Vec2 dis(kinetic->pos);
		dis.subtract(target);
		//maximum change amount. This will be divided by the distance
		Vec2 change(20.0f, 0.0f);//TODO: for now, 10 is a magic number. A better number will be tested or imported from lua
		if (dis.getLength() < EPSILON) {
			//the entity is really really close to the center, move away in max speed in random direction
			float rotateAngle = RandomHelper::random_real<float>(0.0f, PI*2);
			rotateTo(change, rotateAngle);
			//change=change.rotateByAngle(Vec2::ZERO, rotateAngle);
			change.scale(1.0f / EPSILON);
		}
		else {
			rotateTo(change, dis.getAngle());
			change.scale(1.0f / dis.getLength());
		}
		kinetic->vel.add(change);
		if (kinetic->vel.getLength() > kinetic->maxSpeed && kinetic->maxSpeed > 0) {
			kinetic->vel.normalize();
			kinetic->vel.scale(kinetic->maxSpeed);
		}
	}
	else {
		CCLOG("kinetic is null");
	}
}