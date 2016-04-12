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
	if (keyStatus[GameKey::UP]) {
		kineticComp->vel.set(0,1.0);
		kineticComp->resting = false;
	}
	if (keyStatus[GameKey::DOWN])  {
		kineticComp->vel.set(0, -1.0);
		kineticComp->resting = false;
	}
	if (keyStatus[GameKey::LEFT])  {
		kineticComp->vel.set(-1.0, 0);
		kineticComp->resting = false;
	}
	if (keyStatus[GameKey::RIGHT]) {
		kineticComp->vel.set(1.0, 0);
		kineticComp->resting = false;
	}
}
void KeyboardComp::resetVel(Entity* entity) {
	KineticComp* kineticComp = (KineticComp*)entity->components[COMP_CA::KINETIC_COMP];
	kineticComp->resting = true;
	kineticComp->vel.set(0.0, 0.0);
}