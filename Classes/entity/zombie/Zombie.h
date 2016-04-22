#pragma once
#include "entity/Entity.h"
#include "cocos2d.h"
#include "entity/player/Player.h"
#include "entity/zombie/ZombieCatelog.h"

//forward declaration
class Player;

USING_NS_CC;
class Zombie:public Entity {
public:
	Player* player;
	ZOMBIE_CA catagory;
	void init() override;
    Zombie();
	~Zombie() {}
};
