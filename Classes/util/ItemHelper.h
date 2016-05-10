#pragma once
#include "cocos2d.h"
#include "entity/player/Player.h"
#include "component/pooled/PowerUpComp.h"
USING_NS_CC;

namespace item_helper{
	//followings are ideally not be called. 
	void getHealth(Player* player);
	void getAttackBoost(Player* player);
	void getSpeedBoost(Player* player);
	void getInvin(Player* player);
	void removeAttackBoost(Player* player);
	void removeSpeedBoost(Player* player);
	void removeInvin(Player* player);
	//call the following functions instead.
	void removeItem(Player* player);
	void getItem(Player* player, PowerUpComp* power);

}
