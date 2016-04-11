#pragma once

#include <list>
#include "entity/player/Player.h"
#include "entity/zombie/Zombie.h"
#include "entity/Item/Item.h"

#include "runner/EntityRunner.h"
#include "cocos2d.h"

#include "ObjectPool/ObjectPool.h"


USING_NS_CC;
//World is a singleton class

class World {
private:
	static World * s_instance;
	Node* backgroundNode;
	Node* actionNode;
	ObjectPool<Player> *playerPool;
	ObjectPool<Zombie> *zombiePool;
	ObjectPool<Item> *itemPool;

	World();
	World* initPools();
	World* initPlayers();
public:
	static World *instance() {
		if (!s_instance) {
			s_instance = new World();
		}
		return s_instance;
	}
	std::list<Player*> playerList;
	std::list<EntityRunner*> runnerList;

	Player* swiss;
    /**
	*	get called at the start of each level to initialize the world
	*/
	World* initWorld(Node* backgroundLayer, Node* actionLayer);
	World* initSpriteCache();
	void update(float delta);
	void destroy();
};
