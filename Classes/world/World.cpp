#include "World.h"
#include "Debug.h"
#include "cocos2d.h"
#include "component/ComponentCatalog.h"
#include "world_include.h"
#include "common_include.h"
#include "util/EntityFactory.h"
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
	for (int i = GameKey::KEY_START; i <= GameKey::KEY_END; i++) {
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
	initCommonComps();
	initPools();
	
	initPlayers();
	initZombies(swiss);
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
	this->compPools[COMP_CA::DOMAIN_COMP] = new ObjectPool<DomainComp>();
	this->compPools[COMP_CA::HORDE_STATUS_COMP] = new ObjectPool<HordeStatusComp>();
	this->compPools[COMP_CA::COMBAT_COMP] = new ObjectPool<CombatComp>();
	this->compPools[COMP_CA::HEAL_COMP] = new ObjectPool<HealComp>();
	return this;
}
/*Create and initialize all basic components, they can be linked to any entities so we don't have to create multiple of them*/
World* World::initCommonComps() {
	this->commonComps[COMP_CA::KEYBOARD_COMP] = new KeyboardComp();
	this->commonComps[COMP_CA::CHASING_COMP] = new ChasingComp();
	this->commonComps[COMP_CA::SEPERATION_COMP] = new SeperationComp();
	this->commonComps[COMP_CA::FOLLOWING_COMP] = new FollowingComp();

	return this;
}
/*TODO This function is to be refactor into another file. The world class is getting too fat. It's better to have a helper class that specializes in creating all kinds of players and zombies*/
World* World::initPlayers() {
	auto player = EntityFactory::createPlayer(true);
	this->playerList.push_back(player);
	this->swiss = player;

	auto player2 = EntityFactory::createPlayer(false);
	this->playerList.push_back(player2);
	for (int i = 0; i < 10; i++) {
		this->zombieList.push_back(EntityFactory::createZombie(player2));
	}
	return this;
}
/*TODO: to be refactored*/
World* World::initZombies(Player* player) {
	//create 5 zombies
	for (int i = 0; i < 20; i++) {
		
		this->zombieList.push_back(EntityFactory::createZombie(swiss));
	}
	
	return this;
}


World* World::initRunners() {
	
	//init keyboardRunner
	EntityRunner* runner;
	this->runnerList.push_back(new KeyboardRunner());
	this->runnerList.push_back(new ZombieTallyRunner());
	this->runnerList.push_back(new ZombieFollowRunner());
	this->runnerList.push_back(new KineticRunner());
	this->runnerList.push_back(new AnimRunner());
	return this;
}
void World::destroy() {
	//delete all object
	//if an object is from a pool, use pool.Delete(object);
	this->getActionNode()->removeAllChildren();
}