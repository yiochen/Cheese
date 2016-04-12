#pragma once
#include "entity/Entity.h"
#include "cocos2d.h"

USING_NS_CC;
class Zombie:public Entity {
public:
	void init() override;
    Zombie();
	
};
