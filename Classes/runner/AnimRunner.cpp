#include "AnimRunner.h"
#include "world/World.h"

#include "component/pooled/AnimComp.h"
#include "component/ComponentCatalog.h"
#include "entity/Entity.h"
#include "component/pooled/CombatComp.h"

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
	CombatComp* combatComp = (CombatComp*)entity->components[COMP_CA::COMBAT_COMP];
	if (combatComp && combatComp->isDead) {
		//if the entity is dead, remove from the game. 
		//remove the sprite
		CCLOG("check if zombie is dying");
		entity->sprite->removeFromParentAndCleanup(true);
		entity->sprite = NULL;
		World* world = World::instance();
		if (dynamic_cast<Zombie*>(entity)) {
			CCLOG("deleting zombie");
			world->getZombiePool()->Delete((Zombie*)entity);
		}
		else if (dynamic_cast<Player*>(entity)) {
			CCLOG("deleting player");
			world->getPlayerPool()->Delete((Player*)entity);
		}
		else if (dynamic_cast<Item*>(entity)) {
			CCLOG("deleting item");
			world->getItemPool()->Delete((Item*)entity);
		}
		return;
	}
	//get the AnimComp
	AnimComp* animComp = (AnimComp*)entity->components[COMP_CA::ANIM_COMP];
	if (animComp) {
		animComp->updateAnim(entity);
	}
}