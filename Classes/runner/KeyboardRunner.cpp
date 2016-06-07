#include "KeyboardRunner.h"
#include "world/World.h"
#include "component/ComponentCatalog.h"
#include "entity/Entity.h"
#include "component/basic/KeyboardComp.h"
#include "component/pooled/KineticComp.h"
#include <vector>
KeyboardRunner::KeyboardRunner() {
    
}

void KeyboardRunner::update(float delta) {
	
	World* world = World::instance();

	
	auto keyStatus = world->keyStatus;

	auto gamerIt = world->gamerList.begin();
	while (gamerIt != world->gamerList.end()) {
		Player* gamer = (Player*)(*gamerIt);
		KeyboardComp* keyboardComp = (KeyboardComp*)(gamer->components[COMP_CA::KEYBOARD_COMP]);
		KineticComp* kineticComp = (KineticComp*)(gamer->components[COMP_CA::KINETIC_COMP]);
		if (keyboardComp != NULL) {
			auto keyIt = keyStatus.begin();
			while (keyIt != keyStatus.end() && !(bool)(*keyIt)) {
				keyIt++;
			}

			if (keyIt != keyStatus.end() && (bool)(*keyIt)) keyboardComp->changeVel(gamer);
			else if (!kineticComp->resting) {
				keyboardComp->resetVel(gamer);
				CCLOG("velocity is reset, Swiss is resting");
			}

		}
		else {
			CCLOG("keyboardComp doesn't exist, cannot control the player");
		}
		gamerIt++;
	}
	
}