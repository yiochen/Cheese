#pragma once
#include "entity/Entity.h"
#include "cocos2d.h"
#include "entity/player/Player.h"

//forward declaration
class Player;

USING_NS_CC;
class Zombie:public Entity {
public:
	Player* player;
	void init() override;
    Zombie();
	~Zombie() {}
};
