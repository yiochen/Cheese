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
	//initialize the Pools
	
	//initialize all the game objects/entities

	//initialize all the entity runners
	return this;
}
World* World::initSpriteCache() {
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Assets/spritesheet/swiss/SwissSheet.plist", "Assets/spritesheet/swiss/SwissSheet.png");
	return this;
}

void World::update(float delta) {
	std::list<EntityRunner*>::iterator runnerIt=runnerList.begin();
	while (runnerIt != runnerList.end()) {
		((EntityRunner*)(*runnerIt))->update(delta);
	}
}

World* World::initPools() {
	playerPool = new ObjectPool<Player>();
	zombiePool = new ObjectPool<Zombie>();
	itemPool = new ObjectPool<Item>();
	//init all component pools

	return this;
}
World* World::initPlayers() {
	//create the player and its zombies
	//create Main character
	swiss = playerPool->New();
	swiss->init();
	//create other players
	return this;
}

void World::destroy() {
	//delete all object
	//if an object is from a pool, use pool.Delete(object);
}