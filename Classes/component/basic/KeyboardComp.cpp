#include "KeyboardComp.h"
#include "world/World.h"
#include "util/GameKey.h"
#include "component/pooled/KineticComp.h"

KeyboardComp::KeyboardComp() {
    
}
void KeyboardComp::changeVel(Entity* entity) {
	
	//check arrow key
	auto keyStatus = World::instance()->keyStatus;
	KineticComp* kineticComp = (KineticComp*)entity->components[COMP_CA::KINETIC_COMP];
	if (keyStatus[GameKey::UP]&& !keyStatus[GameKey::RIGHT] && !keyStatus[GameKey::LEFT]) {
		kineticComp->vel.set(0,kineticComp->maxSpeed);
		kineticComp->resting = false;
	}
	else if (keyStatus[GameKey::DOWN] && !keyStatus[GameKey::RIGHT] && !keyStatus[GameKey::LEFT])  {
		kineticComp->vel.set(0, -kineticComp->maxSpeed);
		kineticComp->resting = false;
	}
	else if (keyStatus[GameKey::LEFT] && !keyStatus[GameKey::UP] && !keyStatus[GameKey::DOWN])  {
		kineticComp->vel.set(-kineticComp->maxSpeed, 0);
		kineticComp->resting = false;
	}
	else if (keyStatus[GameKey::RIGHT] && !keyStatus[GameKey::UP] && !keyStatus[GameKey::DOWN]) {
		kineticComp->vel.set(kineticComp->maxSpeed, 0);
		kineticComp->resting = false;
	}
	else {
		kineticComp->vel.set(0, 0);
		if (keyStatus[GameKey::UP]) {
			kineticComp->vel.add(Vec2(0, .7071*kineticComp->maxSpeed));
			kineticComp->resting = false;
		}
		if (keyStatus[GameKey::DOWN]) {
			kineticComp->vel.add(Vec2(0, -.7071*kineticComp->maxSpeed));
			kineticComp->resting = false;
		}
		if (keyStatus[GameKey::RIGHT]) {
			kineticComp->vel.add(Vec2(.7071*kineticComp->maxSpeed,0));
			kineticComp->resting = false;
		}
		if (keyStatus[GameKey::LEFT]) {
			kineticComp->vel.add(Vec2(-.7071*kineticComp->maxSpeed,0));
			kineticComp->resting = false;
		}
	}
}
void KeyboardComp::resetVel(Entity* entity) {
	KineticComp* kineticComp = (KineticComp*)entity->components[COMP_CA::KINETIC_COMP];
	kineticComp->resting = true;
	kineticComp->vel.set(0.0, 0.0);
}