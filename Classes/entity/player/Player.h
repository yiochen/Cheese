#pragma once
#include "entity/Entity.h"
#include "entity/zombie/Zombie.h"
#include "cocos2d.h"
#include <list>

USING_NS_CC;

class Player:public Entity {
private:
	//TODO: for now, thoses fields are here, later on, they will be moved to component
	Sprite* sprite;
public:
	std::list<Zombie*> zombies;
	void init() override;
    Player();
};
