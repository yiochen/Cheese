#include "KineticComp.h"
#include "world/World.h"
#include "util/GameKey.h"
#include "component/pooled/KineticComp.h"
KineticComp::KineticComp() {
    
}
void KineticComp::step(Entity* entity) {
	pos.add(vel);
	dynamic_cast<Player*>(entity)->sprite->setPosition(pos);
	
}
// kinetic runner
//add push it