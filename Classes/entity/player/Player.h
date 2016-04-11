#pragma once
#include "entity/Entity.h"
#include "entity/zombie/Zombie.h"
#include "cocos2d.h"
#include <list>

USING_NS_CC;

class Player:public Entity {
private:
	//Some of the function to be 
	Sprite* sprite;
public:
	std::list<Zombie*> zombies;
	void init() override;
    Player();
};
