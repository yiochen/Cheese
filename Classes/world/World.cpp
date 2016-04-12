#include "World.h"
#include "Debug.h"
#include "cocos2d.h"
#include "component/ComponentCatalog.h"
#include "world_include.h"
#include "common_include.h"
USING_NS_CC;

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
	//initStrayZombie();
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
	this->compPools[COMP_CA::ANIM_COMP] = new ObjectPool<AnimComp>();
	return this;
}
World* World::initPlayers() {
	//create the player and its zombies
	//create Main character
	swiss = playerPool->New();
	swiss->init();

	//keyboard Component
	swiss->components[COMP_CA::KEYBOARD_COMP] = new KeyboardComp();

	//kinetic Component
	KineticComp* kineticComp=COMP_POOL(KineticComp,COMP_CA::KINETIC_COMP)->New();
	swiss->components[COMP_CA::KINETIC_COMP] = kineticComp;
	kineticComp->maxSpeed = 100.0f;
	//TODO kinetic position should be relative to the world;
	kineticComp->pos.set(100, 100);
	kineticComp->vel.set(0, 0);
	//animation Component
	AnimComp* animComp= COMP_POOL(AnimComp, COMP_CA::ANIM_COMP)->New();
	//following is to be read from a file
	animComp->name = "swiss";
	animComp->newAnimState = A_WALK_FORTH;
	swiss->components[COMP_CA::ANIM_COMP] = animComp;

	
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
	this->runnerList.push_back(runner = new AnimRunner());
	return this;
}
void World::destroy() {
	//delete all object
	//if an object is from a pool, use pool.Delete(object);
	this->getActionNode()->removeAllChildren();
}