#include "AnimRunner.h"
#include "world/World.h"

#include "component/pooled/AnimComp.h"
#include "component/ComponentCatalog.h"
#include "entity/Entity.h"

AnimRunner::AnimRunner() {
    
}

void AnimRunner::update(float delta) {
	//get all the entities in the game, update their animation
	
	World* world=World::instance();
	//get all the players
	auto playerIt = world->playerList.begin();
	while (playerIt != world->playerList.end()) {
		//update player's animation
		Player* player = (Player*)(*playerIt);
		runAnimRunner(player);
		
		playerIt++;
	}
	//update all the zombies in the player 
	auto zombieIt =world->zombieList.begin();
	while (zombieIt != world->zombieList.end()) {
		runAnimRunner(*zombieIt);
		zombieIt++;
	}
	auto itemIt = world->itemList.begin();
	while (itemIt != world->itemList.end()) {

		itemIt++;
	}
	
}

void AnimRunner::runAnimRunner(Entity* entity) {
	//get the AnimComp
	AnimComp* animComp = (AnimComp*)entity->components[COMP_CA::ANIM_COMP];
	if (animComp) {
		animComp->updateAnim(entity);
	}
}