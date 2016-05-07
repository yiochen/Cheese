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
USING_NS_CC;
//World is a singleton class
#define GET_WORLD World::instance()
class World {
private:
	static World * s_instance;
	Node* backgroundNode;
	Node* actionNode;
	ObjectPool<Player> *playerPool;
	ObjectPool<Zombie> *zombiePool;
	ObjectPool<Item> *itemPool;
	
	Sprite* testSprite;
	TextureManager* textureManager;
	ZombieSpawningPool* spawningPool;
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
	std::list<Player*> playerList;
	std::list<Zombie*> zombieList;
	std::list<Item*> itemList;
	std::list<EntityRunner*> runnerList;
	std::unordered_map<COMP_CA, Comp*> commonComps;
	std::vector<bool> keyStatus;
	//compPools contains all the component pool for managing PooledComponets.
	std::unordered_map<COMP_CA, void *> compPools;
	Player* swiss;
	Player* strayZombie;
    /**
	*	get called at the start of each level to initialize the world
	*/
	World* initWorld(Node* backgroundLayer, Node* actionLayer);
	World* initSpriteCache();
	Node* getBackgroundNode() { return backgroundNode; }
	Node* getActionNode() { return actionNode; }
	TextureManager* getTextureManager() { return textureManager; }
	ObjectPool<Player> *getPlayerPool(){ return playerPool; }
	ObjectPool<Zombie> *getZombiePool(){ return zombiePool; }
	ObjectPool<Item> *getItemPool(){ return itemPool; }
	template <typename T> 
	ObjectPool<T> *getCompPool(COMP_CA typeEnum) {return (ObjectPool<T>*)this->compPools[typeEnum];}
	void update(float delta);
	void destroy();
};
