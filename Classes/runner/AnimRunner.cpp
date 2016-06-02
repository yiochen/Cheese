#include "AnimRunner.h"
#include "world/World.h"

#include "component/pooled/HordeStatusComp.h"

#include "component/pooled/AnimComp.h"
#include "component/ComponentCatalog.h"
#include "entity/Entity.h"
#include "component/pooled/CombatComp.h"
#include "component/pooled/PointComp.h"

AnimRunner::AnimRunner() {
    
}

void AnimRunner::update(float delta) {
	//get all the entities in the game, update their animation
	
	World* world=World::instance();
	//get all the players
	auto playerIt = world->playerList.begin();
	while (playerIt != world->playerList.end()) {
		//update player's animation
		if (runAnimRunner(*playerIt)) {
			Player* entity = (Player*)(*playerIt);
			CCLOG("deleting player");
			playerIt = world->playerList.erase(playerIt);
			world->getPlayerPool()->Delete((Player*)entity);
		}
		else playerIt++;
		
		
		
	}
	//update all the zombies in the player 
	auto zombieIt =world->zombieList.begin();
	while (zombieIt != world->zombieList.end()) {
		/*
		if (runAnimRunner(*zombieIt)) {
			world->zombieList.erase(zombieIt);
			Zombie* entity = (Zombie*)(*zombieIt);
			CCLOG("deleting zombie");
			world->getZombiePool()->Delete((Zombie*)entity);
			
		}
		*/
		if (runAnimRunner(*zombieIt)) {
			
			Zombie* entity = (Zombie*)(*zombieIt);
			if (entity->player) {
				HordeStatusComp* hordeStatus = static_cast<HordeStatusComp*>(entity->player->components[COMP_CA::HORDE_STATUS_COMP]);
				hordeStatus->total--;
				hordeStatus->zombieCounts[entity->category]--;
			}
			CCLOG("deleting zombie");
			if (entity->player != world->swiss) {
				world->score += 2;
				PointComp* point = static_cast<PointComp*>(entity->player->components[COMP_CA::POINT_COMP]);
				point->add(entity->player,2);
			}

			zombieIt = world->zombieList.erase(zombieIt);
			world->getZombiePool()->Delete((Zombie*)entity);
			

		}
		else zombieIt++;
		
	}
	auto itemIt = world->itemList.begin();
	while (itemIt != world->itemList.end()) {
		Item* entity = (Item*)(*itemIt);
		if (runAnimRunner(*itemIt)) {
			CCLOG("removing item");
			Item* item = (Item*)(*itemIt);
			itemIt = world->itemList.erase(itemIt);
			world->getItemPool()->Delete(entity);
		}else itemIt++;
	}
	
}
/*return true when the entity should be removed from the list*/
bool AnimRunner::runAnimRunner(Entity* entity) {
	if (!entity) return false;
	if (entity->marked) return true;
	if (entity->sprite == NULL) {
		entity->marked = true;
		CCLOG("sprite is already deleted, proceed to deleting the entity");
		return true;//if the entity's sprite is set to NULL, delete the entity
	}
	CombatComp* combatComp = (CombatComp*)entity->components[COMP_CA::COMBAT_COMP];
	if (combatComp && combatComp->isDead) {
		//if the entity is dead, remove from the game. 
		//remove the sprite
		CCLOG("check if zombie is dying");
		entity->sprite->removeFromParentAndCleanup(true);
		entity->sprite = NULL;
		entity->marked = true;
		/*World* world = World::instance();
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
		}*/
		return true;
	}
	//get the AnimComp
	AnimComp* animComp = (AnimComp*)entity->components[COMP_CA::ANIM_COMP];
	if (animComp) {
		//CCLOG("updating anim");
		animComp->updateAnim(entity);
	}
	return entity->marked;
}