#pragma once

#include <list>
#include <vector>
#include "entity/player/Player.h"
#include "entity/zombie/Zombie.h"
#include "entity/Item/Item.h"

#include "runner/EntityRunner.h"
#include "cocos2d.h"

#include "ObjectPool/ObjectPool.h"
#include "util/ZombieSpawningPool.h"
#include "graphics/TextureManager.h"
#include "util/GameKey.h"
#include <unordered_map>
#include "entity/attachment/Attachment.h"
#include "util/InformationPanel.h"
USING_NS_CC;
//World is a singleton class
#define GET_WORLD World::instance()
class World {
private:
	static World * s_instance;
	Node* backgroundNode;
	Node* actionNode;
	Node* hudNode;
	ObjectPool<Player> *playerPool;
	ObjectPool<Zombie> *zombiePool;
	ObjectPool<Item> *itemPool;

	ObjectPool<Attachment> *attachmentPool;

	TextureManager* textureManager;
	World();
	World* initPools();
	World* initPlayers();
	World* initRunners();
	World* initCommonComps();
	//World* initStrayZombie();
public:
	static World *instance() {
		if (!s_instance) {
			s_instance = new World();
		}
		return s_instance;
	}
	~World();
	//HUD STUFF, should be in game scene? Could be here
	InformationPanel* infoPanel;
	bool destroyFlag;
	int score;
	ZombieSpawningPool* spawningPool;

	std::list<Player*> playerList;
	std::list<Zombie*> zombieList;
	std::list<Item*> itemList;
	std::list<EntityRunner*> runnerList;
	std::unordered_map<COMP_CA, Comp*> commonComps;
	std::vector<bool> keyStatus;
	//compPools contains all the component pool for managing PooledComponets.
	std::unordered_map<COMP_CA, void *> compPools;
	Player* swiss;
    /**
	*	get called at the start of the game to initialize the world
	*/
	World* initWorld(Node* backgroundLayer, Node* actionLayer, Node* hudNode);
	/**Get called at each level to initialize the game world*/
	World* initWorldData();
	World* initSpriteCache();
	Node* getBackgroundNode() { return backgroundNode; }
	Node* getActionNode() { return actionNode; }
	Node* getHUDNode() { return hudNode; }
	TextureManager* getTextureManager() { return textureManager; }
	ObjectPool<Player> *getPlayerPool(){ return playerPool; }
	ObjectPool<Zombie> *getZombiePool(){ return zombiePool; }
	ObjectPool<Item> *getItemPool(){ return itemPool; }
	ObjectPool<Attachment> *getAttPool() { return attachmentPool; }
	template <typename T> 
	ObjectPool<T> *getCompPool(COMP_CA typeEnum) {return static_cast<ObjectPool<T>*>(this->compPools[typeEnum]);}
	void update(float delta);
	void destroy();
	void destroyData();
};
