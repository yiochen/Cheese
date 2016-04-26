#include "ActionFlagRunner.h"
#include "world/World.h"
#include "component/pooled/ActionFlagComp.h"
ActionFlagRunner::ActionFlagRunner() {
    
}

void ActionFlagRunner::update(float delta) {
	//get all the entities
	World* world = World::instance();
	//playerlist
	auto playerIt = world->playerList.begin();
	while (playerIt != world->playerList.end()) {
		updateEntity(*playerIt, delta);
		playerIt++;
	}
	auto zombieIt = world->zombieList.begin();
	while (zombieIt != world->zombieList.end()) {
		updateEntity(*zombieIt, delta);
		zombieIt++;
	}
	auto itemIt = world->itemList.begin();
	while (itemIt != world->itemList.end()) {
		updateEntity(*itemIt, delta);
		itemIt++;
	}
}
void ActionFlagRunner::updateEntity(Entity* entity, float delta) {
	auto comp =(ActionFlagComp*) entity->components[COMP_CA::ACTION_FLAG_COMP];
	if (comp) {
		comp->update(delta);
	}
}
