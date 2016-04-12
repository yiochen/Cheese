#include "World.h"
#include "Debug.h"

#include "component/ComponentCatalog.h"
#include "world_include.h"

#define COMP_POOL(type, typeEnum) ((ObjectPool<type>*)(this->compPools[typeEnum]))

//Initialize the pointer to be null;
World * World::s_instance = NULL;

//constructor construct the world and create the properties that will last for multiple levels
World::World() {
	playerPool = NULL;
	zombiePool = NULL;
	itemPool = NULL;
	textureManager = NULL;
	CCLOG("start is %d", GameKey::START);
	for (int i = GameKey::START; i <= GameKey::END; i++) {
		keyStatus.push_back(false);
	}
}

//init world init game for a certain level
World* World::initWorld(Node* backgroundLayer, Node* actionLayer) {
	
	this->backgroundNode = backgroundLayer;
	this->actionNode = actionLayer;
	CCLOG("Created the world");
	//initialize the Pools
	initSpriteCache();
	//initialize all the game objects/entities
	initPools();
	initPlayers();
	initStrayZombie();
	//initialize all the entity runners
	initRunners();
	return this;
}
World* World::initSpriteCache() {
	if (this->textureManager == NULL) {
		textureManager = new TextureManager();
		textureManager->init();
	}
	textureManager->load();
	return this;
}

void World::update(float delta) {
	std::list<EntityRunner*>::iterator runnerIt=runnerList.begin();
	while (runnerIt != runnerList.end()) {
		((EntityRunner*)(*runnerIt))->update(delta);
		runnerIt++;
	}
}

World* World::initPools() {
	if (NULL==playerPool) playerPool = new ObjectPool<Player>();
	if (NULL==zombiePool) zombiePool = new ObjectPool<Zombie>();
	if (NULL==itemPool) itemPool = new ObjectPool<Item>();
	//init all component pools
	//register PooledComp to compPools. Otherwise, they cannot be retrieved. 
	this->compPools[COMP_CA::KINETIC_COMP] = new ObjectPool<KineticComp>();
	return this;
}
World* World::initPlayers() {
	//create the player and its zombies
	//create Main character
	swiss = playerPool->New();
	swiss->init();
	swiss->components[COMP_CA::KEYBOARD_COMP] = new KeyboardComp();
	swiss->components[COMP_CA::KINETIC_COMP] = COMP_POOL(KineticComp,COMP_CA::KINETIC_COMP)->New();
	KineticComp* kineticComp = (KineticComp*)(swiss->components[COMP_CA::KINETIC_COMP]);
	kineticComp->maxSpeed = 4.0;
	this->playerList.push_back(swiss);
	//create other players
	return this;
}

World* World::initStrayZombie() {
	//create the owner of stray zombies
	strayZombie = playerPool->New();
	strayZombie->initStrayZombie();
	

	Zombie* zombie1 = zombiePool->New();
	zombie1->init();
	zombie1->components[COMP_CA::KINETIC_COMP] = COMP_POOL(KineticComp,COMP_CA::KINETIC_COMP)->New();;
	KineticComp* kineticComp = (KineticComp*)(zombie1->components[COMP_CA::KINETIC_COMP]);
	kineticComp->maxSpeed = 0.25;
	kineticComp->setPos(100, 100);
	strayZombie->zombies.push_back(zombie1);
	
	Zombie* zombie2 = zombiePool->New();
	zombie2->init();
	zombie2->components[COMP_CA::KINETIC_COMP] = COMP_POOL(KineticComp,COMP_CA::KINETIC_COMP)->New();;
	KineticComp* kineticComp2 = (KineticComp*)(zombie2->components[COMP_CA::KINETIC_COMP]);
	kineticComp2->maxSpeed = 1.0;
	kineticComp2->setPos(0, 300);
	strayZombie->zombies.push_back(zombie2);


	return this;


}


World* World::initRunners() {
	
	//init keyboardRunner
	EntityRunner* runner;
	this->runnerList.push_back(runner=new KeyboardRunner());
	this->runnerList.push_back(runner = new KineticRunner());
	return this;
}
void World::destroy() {
	//delete all object
	//if an object is from a pool, use pool.Delete(object);
}