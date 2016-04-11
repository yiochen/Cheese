#include "World.h"
#include "Debug.h"
//Initialize the pointer to be null;
World * World::s_instance = NULL;

World::World() {
	
}

World* World::initWorld(Node* backgroundLayer, Node* actionLayer) {
	
	this->backgroundNode = backgroundLayer;
	this->actionNode = actionLayer;
	CCLOG("Created the world");
	//initialize all the game objects/entities

	//initialize all the entity runners
	return this;
}

void World::update(float delta) {
	std::list<EntityRunner*>::iterator runnerIt=runnerList.begin();
	while (runnerIt != runnerList.end()) {
		((EntityRunner*)(*runnerIt))->update(delta);
	}
}

World* World::initPlayers() {
	//create the player and its zombies
	
	//create other players
}