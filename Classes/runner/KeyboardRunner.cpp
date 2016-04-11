#include "KeyboardRunner.h"
#include "world/World.h"
#include "component/ComponentCatalog.h"
#include "entity/Entity.h"
#include "component/basic/KeyboardComp.h"
#include <vector>
KeyboardRunner::KeyboardRunner() {
    
}

void KeyboardRunner::update(float delta) {
	
	//I know that only Swiss will be affected by keyboard input directly, so I just get Swiss
	auto keyStatus = World::instance()->keyStatus;
	auto swiss=World::instance()->swiss;
	
	KeyboardComp* keyboardComp =(KeyboardComp*)(swiss->components[COMP_CA::KEYBOARD_COMP]);
	if (keyboardComp != NULL) {
		auto keyIt = keyStatus.begin();
		while (keyIt != keyStatus.end() && !(bool)(*keyIt)) {
			keyIt++;
		}
		
		if (keyIt != keyStatus.end() && (bool)(*keyIt)) keyboardComp->changeVel(swiss);
	}
	else {
		CCLOG("keyboardComp doesn't exist, cannot control the player");
	}
}