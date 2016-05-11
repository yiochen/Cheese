#include "World.h"
#include "Debug.h"
#include "cocos2d.h"
#include "component/ComponentCatalog.h"
#include "world_include.h"
#include "common_include.h"
#include "util/EntityFactory.h"
#include "util/AttachmentFactory.h"
#include "world/Config.h"
#include "world/WorldHelper.h"
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
	spawningPool = NULL;
	attachmentPool = NULL;
	for (int i = GameKey::KEY_START; i <= GameKey::KEY_END; i++) {
		keyStatus.push_back(false);
	}
	destroyFlag = false;
}

//init world init game for a certain level
World* World::initWorld(Node* backgroundLayer, Node* actionLayer, Node* HUDnode) {
	this->backgroundNode = backgroundLayer;
	this->actionNode = actionLayer;
	this->hudNode = HUDnode;
	swiss = NULL;
	score = 0;
	CCLOG("Created the world");
	//initialize the Pools
	initSpriteCache();
	//initialize all the game objects/entities
	initCommonComps();
	initPools();
	initPlayers();
	//initialize all the entity runners
	
	initRunners();
	infoPanel = new InformationPanel();

	if (!Config::instance()->debug_mode) {//if debug mode is turned off
		spawningPool = new ZombieSpawningPool();
		if (spawningPool) spawningPool->init();
	}

	destroyFlag = false;
	
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
	//CCLOG("the total number of zombies in the list is %d", zombieList.size());
	std::list<EntityRunner*>::iterator runnerIt=runnerList.begin();
	while (runnerIt != runnerList.end()) {
		((EntityRunner*)(*runnerIt))->update(delta);
		runnerIt++;
	}
	if (spawningPool) {
		spawningPool->update(delta);
	}
	
	
}

World* World::initPools() {
	if (NULL==playerPool) playerPool = new ObjectPool<Player>();
	if (NULL==zombiePool) zombiePool = new ObjectPool<Zombie>();
	if (NULL==itemPool) itemPool = new ObjectPool<Item>();
	if (NULL == attachmentPool) attachmentPool = new ObjectPool<Attachment>();
	//init all component pools
	//register PooledComp to compPools. Otherwise, they cannot be retrieved. 
	this->compPools[COMP_CA::KINETIC_COMP] = new ObjectPool<KineticComp>();
	this->compPools[COMP_CA::ANIM_COMP] = new ObjectPool<AnimComp>();
	this->compPools[COMP_CA::DOMAIN_COMP] = new ObjectPool<DomainComp>();
	this->compPools[COMP_CA::HORDE_STATUS_COMP] = new ObjectPool<HordeStatusComp>();
	this->compPools[COMP_CA::COMBAT_COMP] = new ObjectPool<CombatComp>();
	this->compPools[COMP_CA::ACTION_FLAG_COMP] = new ObjectPool<ActionFlagComp>();
	this->compPools[COMP_CA::WANDERING_COMP] = new ObjectPool<WanderingComp>();
	this->compPools[COMP_CA::TRAJECT_COMP] = new ObjectPool<TrajectComp>();
	this->compPools[COMP_CA::POINT_COMP] = new ObjectPool<PointComp>();
	this->compPools[COMP_CA::POWER_UP_COMP] = new ObjectPool<PowerUpComp>();
	return this;
}
/*Create and initialize all basic components, they can be linked to any entities so we don't have to create multiple of them*/
World* World::initCommonComps() {
	this->commonComps[COMP_CA::KEYBOARD_COMP] = new KeyboardComp();
	this->commonComps[COMP_CA::CHASING_COMP] = new ChasingComp();
	this->commonComps[COMP_CA::SEPERATION_COMP] = new SeperationComp();
	this->commonComps[COMP_CA::FOLLOWING_COMP] = new FollowingComp();
	this->commonComps[COMP_CA::MELEE_ATTACK_COMP] = new MeleeAttackComp();
	this->commonComps[COMP_CA::RECRUIT_COMP] = new RecruitComp();
	this->commonComps[COMP_CA::RANGE_ATTACK_COMP] = new RangeAttackComp();
	this->commonComps[COMP_CA::HEAL_COMP] = new HealComp();
	return this;
}
/*TODO This function is to be refactor into another file. The world class is getting too fat. It's better to have a helper class that specializes in creating all kinds of players and zombies*/
World* World::initPlayers() {
	
	this->swiss = EntityFactory::createPlayer(true, false,0);
	//create attachment example below
	//AttachmentFactory::createHealAtt(swiss);
	//AttachmentFactory::createExplodeAtt(swiss);
	//AttachmentFactory::createExplodeAtt(swiss);
	//AttachmentFactory::createTargetAtt(swiss);

	//create Item as followed
	if (Config::instance()->debug_mode) {
		EntityFactory::createPickUp(ITEM_CA::ITEM_ATTACK, Vec2(50, 50));
		EntityFactory::createPickUp(ITEM_CA::ITEM_SPEED, Vec2(200, 50));
		EntityFactory::createPickUp(ITEM_CA::ITEM_INVIN, Vec2(300, 50));
	}
	



	return this;
}



World* World::initRunners() {
	
	//init keyboardRunner
	EntityRunner* runner;
	this->runnerList.push_back(new ActionFlagRunner());
	this->runnerList.push_back(new KeyboardRunner());
	this->runnerList.push_back(new ZombieTallyRunner());
	this->runnerList.push_back(new ZombieFollowRunner());
	this->runnerList.push_back(new WandererRunner());
	this->runnerList.push_back(new KineticRunner());
	this->runnerList.push_back(new PickUpRunner());
	this->runnerList.push_back(new TrajectRunner());
	this->runnerList.push_back(new RecruitRunner());
	this->runnerList.push_back(new MeleeAttackRunner());
	this->runnerList.push_back(new RangeAttackRunner());
	this->runnerList.push_back(new HealRunner());
	this->runnerList.push_back(new StatRunner());
	this->runnerList.push_back(new AttachmentAnimRunner());
	this->runnerList.push_back(new EscapeRunner());
	this->runnerList.push_back(new AnimRunner());
	
	return this;
}
void World::destroy() {
	//delete all object
	//if an object is from a pool, use pool.Delete(object);
	infoPanel = NULL;
	//pop_back will call the destructor of the object in the list, which is pointer, and the destructor of pointer does nothing. We need to call the destructor by ourself
	auto runnerIt = runnerList.begin();
	while (runnerIt != runnerList.end()) {
		delete (EntityRunner*)(*runnerIt);
		runnerIt = runnerList.erase(runnerIt);
		//call the destructor of the EntityRunner
	}

	//player, zombie and item are from ObjectPool, return them to the pool and destroy the pool
	/*playerPool = new ObjectPool<Player>();
	zombiePool = new ObjectPool<Zombie>();
	itemPool = new ObjectPool<Item>();
	attachmentPool = new ObjectPool<Attachment>();*/
	auto playerIt = playerList.begin();
	while (playerIt != playerList.end()) {
		playerPool->Delete(*playerIt);
		playerIt = playerList.erase(playerIt);
	}
	/*while (playerList.size() > 0) {
	Player* player = this->playerList.back();
	playerPool->Delete(player);
	this->playerList.pop_back();
	}*/
	//delete the PlayerPool tool
	delete this->playerPool;
	this->playerList.clear();
	this->swiss = nullptr;

	auto zombieIt = zombieList.begin();
	while (zombieIt != zombieList.end()) {
		zombiePool->Delete(*zombieIt);
		zombieIt = zombieList.erase(zombieIt);
	}
	delete this->zombiePool;
	this->zombieList.clear();
	//itemList
	auto itemIt = itemList.begin();
	while (itemIt != itemList.end()) {
		itemPool->Delete(*itemIt);
		itemIt = itemList.erase(itemIt);
	}
	delete this->itemPool;
	this->itemList.clear();
	//remove attachment pool
	delete this->attachmentPool;

	//deleting comp pool
	world_helper::destroyCompPools(this);
	//deleting common comp

	auto commonIt = this->commonComps.begin();
	while (commonIt != this->commonComps.end()) {
		Comp* comp = commonIt->second;
		if (comp) {
			delete comp;
		}
		commonIt=this->commonComps.erase(commonIt);
	}
	this->commonComps.clear();
	this->backgroundNode = NULL;
	
	this->hudNode = NULL;
	//also need to unload sprite cache
	//this->getActionNode()->removeAllChildren();
	delete spawningPool;
	delete textureManager;
	
	playerPool = NULL;
	zombiePool = NULL;
	itemPool = NULL;
	textureManager = NULL;
	spawningPool = NULL;
	attachmentPool = NULL;
}

World::~World() {
	CCLOG("Cleaning up world");
	this->destroy();
}

