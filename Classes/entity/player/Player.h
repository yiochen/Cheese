#pragma once
#include "entity/Entity.h"
#include "entity/zombie/Zombie.h"
#include "cocos2d.h"
#include <list>

USING_NS_CC;

class Player:public Entity {

public:
	void init() override;

    Player();
	~Player();
};
