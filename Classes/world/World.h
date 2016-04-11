#pragma once

#include <list>
#include <vector>
#include "entity/player/Player.h"
#include "entity/zombie/Zombie.h"
#include "entity/Item/Item.h"

#include "runner/EntityRunner.h"
#include "cocos2d.h"

#include "ObjectPool/ObjectPool.h"
#include "graphics/TextureManager.h"
#include "util/GameKey.h"
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
	Sprite* testSprite;
	TextureManager* textureManager;
	World();
	World* initPools();
	World* initPlayers();
	World* initRunners();
public:
	static World *instance() {
		if (!s_instance) {
			s_instance = new World();
		}
		return s_instance;
	}
	std::list<Player*> playerList;
	std::list<EntityRunner*> runnerList;
	std::vector<bool> keyStatus;

	Player* swiss;
    /**
	*	get called at the start of each level to initialize the world
	*/
	World* initWorld(Node* backgroundLayer, Node* actionLayer);
	World* initSpriteCache();
	Node* getBackgroundNode() { return backgroundNode; }
	Node* getActionNode() { return actionNode; }
	TextureManager* getTextureManager() { return textureManager; }
	void update(float delta);
	void destroy();
};
