#include "KineticRunner.h"
#include "world/World.h"
#include "component/ComponentCatalog.h"
#include "entity/Entity.h"
#include "component/pooled/KineticComp.h"
#include <vector>

KineticRunner::KineticRunner() {

}

void KineticRunner::update(float delta) {
	//get all the players, update their pos
	//get all the zombies, update their pos
	//get all the items, update their pos

	World* world = World::instance();
	auto playerIt = world->playerList.begin();
	while (playerIt != world->playerList.end()) {
		Player* player = (Player*)(*playerIt);
		updateEntity(player, delta);
		
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

//update a single entity
void KineticRunner::updateEntity(Entity* entity, float delta) {
	//check if the entity has kinetic component
	KineticComp* kinComp = static_cast<KineticComp*>(entity->components[COMP_CA::KINETIC_COMP]);
	if (kinComp) {
		kinComp->step(entity, delta);
	}

}

