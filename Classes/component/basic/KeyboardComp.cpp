#include "KeyboardComp.h"
#include "world/World.h"
#include "util/GameKey.h"

KeyboardComp::KeyboardComp() {
    
}
void KeyboardComp::changeVel(Entity* entity) {
	
	//check arrow key
	auto keyStatus = World::instance()->keyStatus;
	if (keyStatus[GameKey::UP]) CCLOG("up!!!");
	if (keyStatus[GameKey::DOWN]) CCLOG("down!!");
	if (keyStatus[GameKey::LEFT]) CCLOG("left!!");
	if (keyStatus[GameKey::RIGHT]) CCLOG("right!!");
}